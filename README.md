1. The TradeData folder has multiple .csv files each representing a tradable script
2. TradeData timestamp is of nano-seconds precision
3. Program a fast and  efficient method to read these files (the size of original files is of order 50-60GB)
and update the given data structure with next suitable data set (next time stamp available across all files)
4. the structure  ScriptQuote will be updated with the next suitable data whenever NextData() function is called

struct ScriptQuote
{
 int32_t bid[5]
      int32_t ask[5]
      int32_t ltp
      int32_t volume
      char*   ScriptName
      long long TmFrame
}

DataFormat: Time,BidQty1,..,..,..,BidQty5,Bid1,..,..,..,Bid5,Ask1,..,..,..,Ask5,AskQty1,..,..,..,AskQty5,O,H,L,Ltp,Volume,ignore

Output format:-
ScriptName,TimeStamp,Bid1,Bid2,Bid3,Bid4,Bid5,Ask1,Ask2,Ask3,Ask4,Ask5
