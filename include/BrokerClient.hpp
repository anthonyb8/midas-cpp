#ifndef MY_WRAPPER
#define MY_WRAPPER

#include "EWrapper.h"
#include <string>

class MyWrapper : public EWrapper {
public:
	void error(int id, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson) override;
	void connectionClosed() override;
	void connectAck() override; 
	void nextValidId( OrderId orderId) override;
	void contractDetails( int reqId, const ContractDetails& contractDetails) override;
	void contractDetailsEnd( int reqId) override;
	void updateAccountTime(const std::string& timeStamp) override;
	void updateAccountValue(const std::string& key, const std::string& val,const std::string& currency, const std::string& accountName) override;
	void updatePortfolio( const Contract& contract, Decimal position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName) override;
	void accountDownloadEnd(const std::string& accountName) override;
	void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&) override;
	void openOrderEnd() override;
	void execDetails( int reqId, const Contract& contract, const Execution& execution) override;
	void execDetailsEnd( int reqId) override;
	void orderStatus( OrderId orderId, const std::string& status, Decimal filled, Decimal remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) override;
	void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, Decimal volume, Decimal wap, int count) override;


	void tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib) override;
	void tickSize(TickerId tickerId, TickType field, Decimal size) override;
	void tickString(TickerId tickerId, TickType tickType, const std::string& value) override;
};

#endif