#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );

    return 0;
};

// #include "nlohmann/json.hpp"
// #include <fstream>
// #include <iostream>
// #include <typeinfo>
// #include <vector>
// #include "MidasClient.hpp"


// int main() {
//     std::ifstream i("config.json");
//     nlohmann::json j;
//     i >> j;
//     std::string api_key = j["MIDAS_KEY"].get<std::string>();
// 	MidasClient client(api_key);

//     // Get Symbols
//     std::vector securities = client.get_symbol();
//     for (const auto& sec : securities) {
// 		std::cout << sec.ticker << std::endl;
// 	};

//     // Get Bardata
//     std::string start_date = "2022-05-10";
//     std::string end_date = "2024-05-10";
//     std::vector<std::string> tickers= {"^GSPC", "AAPL2","HE.n.0"};
//     std::vector bardata = client.get_bardata(tickers, start_date, end_date);
//     for (const auto& bar : bardata) {
// 		bar.print();
// 	};

    
//     return 0;
// };
