#ifndef MIDAS_CLIENT_HPP
#define MIDAS_CLIENT_HPP

#include <string>
#include <vector>
#include <chrono>
#include <cstdint> 

struct Security {
    std::string ticker;
    std::string security_type;
};

struct Bardata {
    double open;
    double high;
    double low;
    double close;
	std::int64_t volume;
    std::string ticker;
	std::string timestamp; 

	void print() const {
		std::cout << "Ticker: " << ticker
					<< ", Timestamp: " << timestamp
					<< ", Open: " << open
					<< ", High: " << high
					<< ", Low: " << low
					<< ", Close: " << close
					<< ", Volume: " << volume << std::endl;
	}

};

class MidasClient {
private:
	std::string api_url;
	std::string api_key;

public:
	MidasClient(const std::string& api_key, const std::string& api_url = "http://127.0.0.1:8000/api");
	std::vector<Security> get_symbol();
	std::vector<Bardata> get_bardata(const std::vector<std::string>& tickers, const std::string& start_date, const std::string& end_date);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
	static std::vector<Bardata> parseJsonToBardata(const nlohmann::json& j);
	std::string performHttpRequest(const std::string& url, const std::vector<std::string>& headersVec);
};

#endif // MIDAS_CLIENT_H