#include "audio.h"
 #define CATCH_CONFIG_MAIN
 #include "catch.hpp"


////////////////////////////TESTS//////////////////////////
/************* TESTS FOR STEREO *****************/

/******* FOR STEREO concatination ***********/
// TEST_CASE("audio concatination, STEREO",""){
// 	std::vector<pair<int8_t,int8_t>> v_audio3;
// 	std::vector<pair<int8_t,int8_t>> v_audio4;

// 	for(int i=1;i<6;i++){
// 	v_audio3.push_back(make_pair(i,i+1));
// 	v_audio4.push_back(make_pair(i+1,i+2));
// 	}

// 	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
// 	audio<int8_t,pair<int8_t,int8_t>> aud2(v_audio4);
//	audio<int8_t,pair<int8_t,int8_t>> conct = aud1|aud2;


// REQUIRE(sum.audio_data[0] == 1);
// REQUIRE(sum.audio_data[1] == 1);
// REQUIRE(sum.audio_data[2] == 1);
// REQUIRE(sum.audio_data[3] == 1);
// REQUIRE(sum.audio_data[4] == -1);
// REQUIRE(sum.audio_data[5] == 2);
// REQUIRE(sum.audio_data[6] ==3);
// REQUIRE(sum.audio_data[7] == -11);
// REQUIRE(sum.audio_data[8] == 127);
// REQUIRE(sum.audio_data[9] == -128);
// // REQUIRE(sum.audio_data[5] == 3);}

// TEST_CASE("sound amplitude addition per sample, STEREO",""){
//std::vector<pair<int8_t,int8_t>> v_audio3;
//	std::vector<pair<int8_t,int8_t>> v_audio4;

// 	for(int i=1;i<6;i++){
// 	v_audio3.push_back(make_pair(i,i+1));
// 	v_audio4.push_back(make_pair(i+1,i+2));
// 	}

//	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
//audio<int8_t,pair<int8_t,int8_t>> aud2(v_audio4);

// 	for(auto item: aud1.audio_data)
// 	  cout<<"first is: "<<(int)item.first<<" second is: "<<(int)item.second<<endl;

//concatenate two audio files
// 	audio<int8_t,pair<int8_t,int8_t>> conct = aud1|aud2;
//test  addition of audio files
// audio<int8_t,pair<int8_t,int8_t>> sum = aud1+aud2;

// REQUIRE(sum1.audio_data[0]==3);
// REQUIRE(sum1.audio_data[1] == 5);
// REQUIRE(sum1.audio_data[2] == -9);
// REQUIRE(sum1.audio_data[3] == 127);
// REQUIRE(sum1.audio_data[4] == -128);
// // REQUIRE(sum.audio_data[5] == 3);


// }


// TEST_CASE("volume factor, STEREO",""){
// //	std::vector<pair<int8_t,int8_t>> v_audio3;
// 	std::vector<pair<int8_t,int8_t>> v_audio4;

// 	for(int i=1;i<6;i++){
// 	v_audio3.push_back(make_pair(i,i+1));
// 	v_audio4.push_back(make_pair(i+1,i+2));
// 	}

// 	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
// aud1*pair<float,float>(0.5,0.5);// works
// REQUIRE(aud4.audio_data[0]==1);
// REQUIRE(aud4.audio_data[1] == 2);
// REQUIRE(aud4.audio_data[2] == -5);
// REQUIRE(aud4.audio_data[3] == 50);
// REQUIRE(aud4.audio_data[4] == -20);
// // REQUIRE(sum.audio_data[5] == 3);


// }


// TEST_CASE("cut, STEREO",""){
// //	std::vector<pair<int8_t,int8_t>> v_audio3;
// 	std::vector<pair<int8_t,int8_t>> v_audio4;

// 	for(int i=1;i<6;i++){
// 	v_audio3.push_back(make_pair(i,i+1));
// 	v_audio4.push_back(make_pair(i+1,i+2));
// 	}

// 	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
// aud1^pair<float,float>(0.5,0.5);// works
// REQUIRE(aud4.audio_data[0]==1);
// REQUIRE(aud4.audio_data[1] == 2);
// REQUIRE(aud4.audio_data[2] == -5);
// REQUIRE(aud4.audio_data[3] == 50);
// REQUIRE(aud4.audio_data[4] == -20);
// // REQUIRE(sum.audio_data[5] == 3);


// }

// TEST_CASE("reverse, STEREO",""){
// //	std::vector<pair<int8_t,int8_t>> v_audio3;
// 	std::vector<pair<int8_t,int8_t>> v_audio4;

// 	for(int i=1;i<6;i++){
// 	v_audio3.push_back(make_pair(i,i+1));
// 	v_audio4.push_back(make_pair(i+1,i+2));
// 	}

// 	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
// aud1.reverse()<float,float>(0.5,0.5);// works
// REQUIRE(aud4.audio_data[0]==1);
// REQUIRE(aud4.audio_data[1] == 2);
// REQUIRE(aud4.audio_data[2] == -5);
// REQUIRE(aud4.audio_data[3] == 50);
// REQUIRE(aud4.audio_data[4] == -20);
// // REQUIRE(sum.audio_data[5] == 3);


// }



// TEST_CASE("reverse, STEREO",""){
// //	std::vector<pair<int8_t,int8_t>> v_audio3;
// 	std::vector<pair<int8_t,int8_t>> v_audio4;

// 	for(int i=1;i<6;i++){
// 	v_audio3.push_back(make_pair(i,i+1));
// 	v_audio4.push_back(make_pair(i+1,i+2));
// 	}

// 	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
// audio<int8_t,pair<int8_t,int8_t>>::rangedAdd rAdd;//function object
// audio<int8_t,pair<int8_t,int8_t>> range_sum = rAdd(aud1,0,3,aud2,0,3);
// REQUIRE(aud4.audio_data[0]==1);
// REQUIRE(aud4.audio_data[1] == 2);
// REQUIRE(aud4.audio_data[2] == -5);
// REQUIRE(aud4.audio_data[3] == 50);
// REQUIRE(aud4.audio_data[4] == -20);
// // REQUIRE(sum.audio_data[5] == 3);


// }








/************* TESTS FOR MONO *****************/
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////


 TEST_CASE("audio concatination, mono",""){
   std::vector<int8_t> v_aud1 = {1, 1, 1, 1,-1};
 std::vector<int8_t> v_aud2 = {2, 3, -11, 127, -128};

 audio<int8_t,int8_t> aud1(v_aud1);
 audio<int8_t, int8_t> aud2(v_aud2);
 // audio<int16_t,int16_t> aud3(v_aud1);
 // audio<int16_t, int16_t> aud4(v_aud2);
 audio<int8_t,int8_t> sum =aud1|aud2;


 REQUIRE(sum.audio_data[0] == 1);
 REQUIRE(sum.audio_data[1] == 1);
 REQUIRE(sum.audio_data[2] == 1);
 REQUIRE(sum.audio_data[3] == 1);
 REQUIRE(sum.audio_data[4] == -1);
 REQUIRE(sum.audio_data[5] == 2);
 REQUIRE(sum.audio_data[6] ==3);
 REQUIRE(sum.audio_data[7] == -11);
 REQUIRE(sum.audio_data[8] == 127);
 REQUIRE(sum.audio_data[9] == -128);
 // REQUIRE(sum.audio_data[5] == 3);


 }



 TEST_CASE("volume factor, mono",""){
   std::vector<int8_t> v_aud1 = {1, 1, 1, 1,-1};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 100, -40};

 audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 // audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);
 aud4*pair<float,float>(0.5,0.5);
 aud1*pair<float,float>(0.1,0.5);

 REQUIRE(aud4.audio_data[0]==1);
 REQUIRE(aud4.audio_data[1] == 2);
 REQUIRE(aud4.audio_data[2] == -5);
 REQUIRE(aud4.audio_data[3] == 50);
 REQUIRE(aud4.audio_data[4] == -20);
 // REQUIRE(sum.audio_data[5] == 3);


 }

 TEST_CASE("sound amplitude addition per sample, mono",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 127, -128};

 // audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);
 audio<int16_t,int16_t> sum1 = aud3+aud4;

 REQUIRE(sum1.audio_data[0]==3);
 REQUIRE(sum1.audio_data[1] == 5);
 REQUIRE(sum1.audio_data[2] == -9);
 REQUIRE(sum1.audio_data[3] == 127);
 REQUIRE(sum1.audio_data[4] == -128);
 // REQUIRE(sum.audio_data[5] == 3);


 }


 TEST_CASE("cut implementation, mono",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 127, -128};

 // audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);
 // audio<int16_t,int16_t> sum1 = aud3+aud4;
 aud4 ^ pair<int, int>(0, 1);



 REQUIRE(aud4.audio_data.size()==3);
 REQUIRE(aud4.audio_data[0]==-10);
 REQUIRE(aud4.audio_data[1] == 127);
 }


 TEST_CASE("reverse, mono",""){
   std::vector<int8_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 127, -128};

 audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 // audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);

 aud4.reverse();
 aud1.reverse();
 REQUIRE(aud4.audio_data[0]==-128);
 REQUIRE(aud4.audio_data[1] == 127);
 REQUIRE(aud4.audio_data[2]==-10);
 REQUIRE(aud4.audio_data[3] == 4);
 REQUIRE(aud1.audio_data[0] == -2);
 REQUIRE(aud1.audio_data[1] == 3);
 }

 TEST_CASE("range add, mono",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 127, -128};

 // audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);

 audio<int16_t,int16_t>::rangedAdd rAdd;//function object
 audio<int16_t,int16_t> range_sum = rAdd(aud3,0,3,aud4,0,3);

 REQUIRE(range_sum.audio_data[0]==3);
 REQUIRE(range_sum.audio_data[1] == 5);
 REQUIRE(range_sum.audio_data[2]==-9);
 REQUIRE(range_sum.audio_data[3] == 127);

 }

 TEST_CASE("Compute RMS, mono",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {1, 1, 1, 1, 1};


 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);

 aud3.rms_cal();
 aud4.rms_cal();
 REQUIRE(aud3.rms<2);
 REQUIRE(aud4.rms==1.0);

 }

 TEST_CASE("Normalise, mono",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {1, 1, 1, 1, 1};


 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);

 aud3.rms_cal();
 aud4.rms_cal();
 REQUIRE(aud3.rms<2);
 REQUIRE(aud4.rms==1.0);
}