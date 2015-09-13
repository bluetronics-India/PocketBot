#include "PocketBot.h"

void PocketBot::begin(Stream *stream){
  mStream = stream;
  mBracketOpenCount = 0;
}

bool PocketBot::read(){
  
  while ( mStream->available() ){
    char in = mStream->read();
    if (in == '{') {
		if(mBracketOpenCount == 0){
			mBegin = true;
			mResponse = "";
		}
	   mBracketOpenCount++;
    }
    
    if (mBegin) mResponse += (in);

    if (in == '}') {
		mBracketOpenCount--;
		if(mBracketOpenCount == 0){
			mBegin = false;
			return true;
		}
    }
  }
  return false; 
}

JsonObject& PocketBot::getJson(){
  StaticJsonBuffer<2000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(mResponse);
  if(root.success()){
    
  } 
  return root;
}

void PocketBot::printRawTo(Stream &stream){
	stream.print(mResponse);
}