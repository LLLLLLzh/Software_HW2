/**
 * productservice.hpp defines Bond and IRSwap ProductServices
 */

#include <iostream>
#include <map>
#include "../../Downloads/products/products.hpp"
#include "../../Downloads/products/soa.hpp"

/**
 * Bond Product Service to own reference data over a set of bond securities.
 * Key is the productId string, value is a Bond.
 */
class BondProductService : public Service<string,Bond>
{

public:
    // BondProductService ctor
    BondProductService();

    // Return the bond data for a particular bond product identifier
    Bond& GetData(string productId);

    // Add a bond to the service (convenience method)
    void Add(Bond &bond);

    // Get all Bonds with the specified ticker
    vector<Bond> GetBonds(string& _ticker);

private:
    map<string,Bond> bondMap; // cache of bond products

};

/**
 * Interest Rate Swap Product Service to own reference data over a set of IR Swap products
 * Key is the productId string, value is a IRSwap.
 */
class IRSwapProductService : public Service<string,IRSwap>
{
public:
    // IRSwapProductService ctor
    IRSwapProductService();

    // Return the IR Swap data for a particular bond product identifier
    IRSwap& GetData(string productId);

    // Add a bond to the service (convenience method)
    void Add(IRSwap &swap);

    // Get all Swaps with the specified fixed leg day count convention
    vector<IRSwap> GetSwaps(DayCountConvention _fixedLegDayCountConvention);

    // Get all Swaps with the specified fixed leg payment frequency
    vector<IRSwap> GetSwaps(PaymentFrequency _fixedLegPaymentFrequency);

    // Get all Swaps with the specified floating index
    vector<IRSwap> GetSwaps(FloatingIndex _floatingIndex);

    // Get all Swaps with a term in years greater than the specified value
    vector<IRSwap> GetSwapsGreaterThan(int _termYears);

    // Get all Swaps with a term in years less than the specified value
    vector<IRSwap> GetSwapsLessThan(int _termYears);

    // Get all Swaps with the specified swap type
    vector<IRSwap> GetSwaps(SwapType _swapType);

    // Get all Swaps with the specified swap leg type
    vector<IRSwap> GetSwaps(SwapLegType _swapLegType);


private:
    map<string,IRSwap> swapMap; // cache of IR Swap products

};

BondProductService::BondProductService()
{
    bondMap = map<string,Bond>();
}

Bond& BondProductService::GetData(string productId)
{
    return bondMap[productId];
}

void BondProductService::Add(Bond &bond)
{
    bondMap.insert(pair<string,Bond>(bond.GetProductId(), bond));
}

vector<Bond> BondProductService::GetBonds(string& _ticker){
    vector<Bond> b;
    for(auto it=bondMap.begin();it!=bondMap.end();++it){
        if((it->second).GetTicker()==_ticker)
            b.push_back(it->second);
    }
    return b;
}

IRSwapProductService::IRSwapProductService()
{
    swapMap = map<string,IRSwap>();
}

IRSwap& IRSwapProductService::GetData(string productId)
{
    return swapMap[productId];
}

void IRSwapProductService::Add(IRSwap &swap)
{
    swapMap.insert(pair<string,IRSwap>(swap.GetProductId(), swap));
}

vector<IRSwap> IRSwapProductService::GetSwaps(DayCountConvention _fixedLegDayCountConvention){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetFixedLegDayCountConvention()==_fixedLegDayCountConvention)
			swap.push_back(it->second);
	}
	return swap;
}

vector<IRSwap> IRSwapProductService::GetSwaps(PaymentFrequency _fixedLegPaymentFrequency){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetFixedLegPaymentFrequency()==_fixedLegPaymentFrequency)
			swap.push_back(it->second);
	}
	return swap;
}

vector<IRSwap> IRSwapProductService::GetSwaps(FloatingIndex _floatingIndex){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetFloatingIndex()==_floatingIndex)
			swap.push_back(it->second);
	}
	return swap;
}

vector<IRSwap> IRSwapProductService::GetSwapsGreaterThan(int _termYears){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetTermYears() > _termYears)
			swap.push_back(it->second);
	}
	return swap;
}

vector<IRSwap> IRSwapProductService::GetSwapsLessThan(int _termYears){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetTermYears() < _termYears)
			swap.push_back(it->second);
	}
	return swap;
}

vector<IRSwap> IRSwapProductService::GetSwaps(SwapType _swapType){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetSwapType()==_swapType)
			swap.push_back(it->second);
	}
	return swap;
}

vector<IRSwap> IRSwapProductService::GetSwaps(SwapLegType _swapLegType){
	vector<IRSwap> swap;
	for(auto it=swapMap.begin();it!=swapMap.end();++it){
		if((it->second).GetSwapLegType()==_swapLegType)
			swap.push_back(it->second);
	}
	return swap;
}
