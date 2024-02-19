#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "MidasClient.hpp"

#include <databento/historical.hpp>
#include <databento/log.hpp>

using namespace databento;

class Schemas(Enum):
    MBO='mbo'               // Market by order, full order book, tick data
    MBP_10='mbp-10'	        // L2, market by price, market depth
    MBP_1='mbp-1'	        // L1, top of book, trades and quotes
    TBBO='tbbo'	            // Top of book, sampled in trade space
    Trades='trades'	        // Last sale, time and sales, tick-by-tick trades
    OHLCV_1s='ohlcv-1s'     // OHLCV bars, aggregates
    OHLCV_1m='ohlcv-1m'     // OHLCV bars, aggregates
    OHLCV_1h='ohlcv-1h'     // OHLCV bars, aggregates
    OHLCV_1d='ohlcv-1d'     // OHLCV bars, aggregates
    Definition='definition'	// Security definitions, reference data, symbol list
    Imbalance='imbalance'	// Imbalance auction quotes
    Statistics='statistics' 

class Symbology(Enum):
    RAWSYMBOL='raw_symbol'         // Original string symbols used by the publisher in the source data.
    INSTRUMENT_ID='instrument_id'  // Unique numeric ID assigned to each instrument by the publisher.
    PARENTSYMBOL='parent'          // Groups instruments related to the market for the same underlying.
    CONTINUOSCONTRACT='continuous' // Proprietary symbology that specifies instruments based on certain systematic rules.

class Datasets(Enum):   
    NASDAQ='XNAS.ITCH'               // Nasdaq TotalView-ITCH is the proprietary data feed that provides full order book depth for Nasdaq market participants.
    CME='GLBX.MDP3'                  // MDP 3.0 is the sole data feed for all instruments traded on CME Globex, including futures, options, spreads and combinations.
    OPRA='OPRA.PILLAR'               // Options data. Consolidated last sale, exchange BBO and national BBO across all US equity options exchanges
    DATABENTOEQUITIES='DBEQ.BASIC'   // A consolidation of US equities prop feeds that’s free to license for all use cases. 
    

class DatabentoClient {
private:
	std::string api_key;
	auto client;

public:
	DatabentoClient(const std::string& api_key){
		auto client = Historical{ILogReceiver::Default(), api_key, HistoricalGateway::Bo1};

	}

	auto print_trades = [](const Record record) {
        // Convert the generic `Record` to a `TradeMsg`, the record
        // type associated with `Schema::Trades`
        const auto& trade_msg = record.Get<OhlcvMsg>();
        std::cout << trade_msg << '\n';
        return KeepGoing::Continue;
        };

	std::string get_historical(symbols:list, schema:Schemas,dataset:Datasets,stype:Symbology, start_date=None, end_date=None){
		    client.TimeseriesGetRange(
            "GLBX.MDP3", {"2022-06-06T00:00", "2022-06-10T00:10"},
            {"ESM2"}, Schema::Ohlcv1D, SType::RawSymbol,
            SType::InstrumentId, 1, {}, print_trades);
	}
    return 0;
};


    // auto print_trades = [](const Record record) {
    //     // Convert the generic `Record` to a `TradeMsg`, the record
    //     // type associated with `Schema::Trades`
    //     const auto& trade_msg = record.Get<OhlcvMsg>();
    //     std::cout << trade_msg << '\n';
    //     return KeepGoing::Continue;
    //     };

    // // std::vector<Record> records;

    // // auto collect_records = [&records](const Record& record) {
    // //     // Simply add the record to the vector
    // //     records.push_back(record);

    // //     return KeepGoing::Continue;
    // // };
        
    // client.TimeseriesGetRange(
    //         "GLBX.MDP3", {"2022-06-06T00:00", "2022-06-10T00:10"},
    //         {"ESM2"}, Schema::Ohlcv1D, SType::RawSymbol,
    //         SType::InstrumentId, 1, {}, print_trades);

    // // Example of processing records after they have been collected
    // for (const auto& record : records) {
    //     // Assuming Record has a method or a way to be outputted directly
    //     // You may need to replace this with actual code to access Record's data
    //     std::cout << record << '\n'; // This assumes that operator<< is overloaded for Record
    // }
