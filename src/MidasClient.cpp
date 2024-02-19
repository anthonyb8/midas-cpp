#include <curl/curl.h> 
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include "MidasClient.hpp"


MidasClient::MidasClient(const std::string& api_key, const std::string& api_url)
	: api_key(api_key), api_url(api_url) {}

std::vector<Security> MidasClient::get_symbol() {
	// Create URL and Header
	std::string url = api_url + "/symbols/";
	std::vector<std::string> headers = {
		"Content-Type: application/json",
		"Accept: application/json",
		"Authorization: Token " + api_key
	};
	// 
	std::string response = performHttpRequest(url, headers);
	auto j = nlohmann::json::parse(response);

	// Assign JSON data to vector of Securities
	std::vector<Security> securities;
	for (const auto& item : j) {
		Security sec;
		item.at("ticker").get_to(sec.ticker);
		item.at("security_type").get_to(sec.security_type);
		securities.push_back(sec);
	};

	return securities;
};

std::vector<Bardata> MidasClient::get_bardata(const std::vector<std::string>& tickers, const std::string& start_date, const std::string& end_date){
	// Parse tickers vector into a string seperated by commas
	std::string tickersJoined;
    for(const auto& ticker : tickers) {
        tickersJoined += ticker + ",";
    }
    tickersJoined.pop_back(); // Remove the trailing comma

	// URL
	std::ostringstream oss;
    oss << api_url << "/bardata/?tickers=" << tickersJoined << "&start_date=" << start_date << "&end_date=" << end_date;
    std::string url = oss.str();
	
	// Header
	std::vector<std::string> headers = {
		"Content-Type: application/json",
		"Accept: application/json",
		"Authorization: Token " + api_key
    };
	
	// Make request and parse JSON response 
	std::string response = performHttpRequest(url, headers);
	auto j = nlohmann::json::parse(response);
	
	std::cout << j;

	// // Iterate through response data
	// std::vector<Bardata> bardataVec;
	// for (const auto& item : j){
	// 	Bardata bar;
	// 	item.at("symbol").get_to(bar.ticker);
	// 	item.at("timestamp").get_to(bar.timestamp);
	// 	item.at("open").get_to(bar.open);
	// 	item.at("close").get_to(bar.close);
	// 	item.at("high").get_to(bar.high);
	// 	item.at("low").get_to(bar.low);
	// 	bardataVec.push_back(bar);
	// }
	return parseJsonToBardata(j);
};


std::vector<Bardata> MidasClient::parseJsonToBardata(const nlohmann::json& j) {
    std::vector<Bardata> bardataVec;
    for (const auto& item : j) {
        Bardata bar;
        bar.ticker = item.at("symbol").get<std::string>();
        bar.timestamp = item.at("timestamp").get<std::string>(); // Directly assigned, consider parsing
		bar.volume= item.at("volume").get<std::int64_t>();

        // Convert string to double
        try {
            bar.open = std::stod(item.at("open").get<std::string>());
            bar.close = std::stod(item.at("close").get<std::string>());
            bar.high = std::stod(item.at("high").get<std::string>());
            bar.low = std::stod(item.at("low").get<std::string>());

        } catch (const std::exception& e) {
            std::cerr << "Error converting string to double: " << e.what() << '\n';
            // Handle error or assign default value
        }

        bardataVec.push_back(bar);
    }
    return bardataVec;
};

size_t MidasClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    };

std::string MidasClient::performHttpRequest(const std::string& url, const std::vector<std::string>& headersVec) {
	CURL* curl = curl_easy_init();
	if (!curl) {
		throw std::runtime_error("CURL could not be initialized.");
	}

	// Convert vector of headers to curl_slist
	struct curl_slist* headers = NULL;
	for (const auto& header : headersVec) {
		headers = curl_slist_append(headers, header.c_str());
	}

	std::string readBuffer;
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	CURLcode result = curl_easy_perform(curl);
	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);

	if (result != CURLE_OK || http_code != 200) {
		throw std::runtime_error("HTTP request failed: " + readBuffer);
	}

	return readBuffer;
}