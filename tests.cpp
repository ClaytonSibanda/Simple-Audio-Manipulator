#include "audio.h"
 #define CATCH_CONFIG_MAIN
 #include "catch.hpp"


////////////////////////////TESTS//////////////////////////
/************* TESTS FOR STEREO *****************/

/******* FOR STEREO concatination ***********/
 TEST_CASE("audio concatination, STEREO",""){
 	std::vector<std::pair<int8_t,int8_t>> v_audio3;
 	std::vector<std::pair<int8_t,int8_t>> v_audio4;

 	for(int i=1;i<6;i++){
 	v_audio3.push_back(std::make_pair(i,i+1));
 	v_audio4.push_back(std::make_pair(i+1,i+2));
 	}

 	audio<int8_t,std::pair<int8_t,int8_t>> aud1(v_audio3);
 	audio<int8_t,std::pair<int8_t,int8_t>> aud2(v_audio4);
	audio<int8_t,std::pair<int8_t,int8_t>> aud3 = aud1|aud2;

std::cout<<aud1.audio_data.size()<<std::endl;

 REQUIRE(aud2.audio_data[0].first == 2);
 REQUIRE(aud2.audio_data[0].second == 3);
 REQUIRE(aud2.audio_data[1].first == 3);
 REQUIRE(aud2.audio_data[1].second == 4);
    REQUIRE(aud1.audio_data[2].first == 3);
    REQUIRE(aud1.audio_data[2].second == 4);


 }

 TEST_CASE("SOUNND AMPLITUDE ADDITION PER SAMPLE, STEREO",""){
std::vector<std::pair<int8_t,int8_t>> v_audio3;
std::vector<std::pair<int8_t,int8_t>> v_audio4;

 	for(int i=1;i<6;i++){
 	v_audio3.push_back(std::make_pair(i,i+1));
 	v_audio4.push_back(std::make_pair(i+1,i+2));
 	}

	audio<int8_t,std::pair<int8_t,int8_t>> aud1(v_audio3);
audio<int8_t,std::pair<int8_t,int8_t>> aud2(v_audio4);

// 	for(auto item: aud1.audio_data)
// 	  cout<<"first is: "<<(int)item.first<<" second is: "<<(int)item.second<<endl;

//test  addition of audio files
 audio<int8_t,std::pair<int8_t,int8_t>> sum1 = aud1+aud2;

 REQUIRE(sum1.audio_data[0].first==3);
 REQUIRE(sum1.audio_data[0].second == 5);
 REQUIRE(sum1.audio_data[2].first == 7);
 REQUIRE(sum1.audio_data[2].second ==9);
 REQUIRE(sum1.audio_data[3].first == 9);
REQUIRE(sum1.audio_data[3].second == 11);


 }


 TEST_CASE("VOLUME FACTOR, STEREO",""){
 	std::vector<std::pair<int8_t,int8_t>> v_audio3;
 	std::vector<std::pair<int8_t,int8_t>> v_audio4;

 	for(int i=1;i<6;i++){
 	v_audio3.push_back(std::make_pair(i,i+1));
 	v_audio4.push_back(std::make_pair(i+1,i+2));
 	}

 	audio<int8_t,std::pair<int8_t,int8_t>> aud1(v_audio3);
 aud1*std::pair<float,float>(0.5,0.5);// works

 REQUIRE(aud1.audio_data[0].first==0);
 REQUIRE(aud1.audio_data[1].first == 1);
 REQUIRE(aud1.audio_data[1].second ==1);
 REQUIRE(aud1.audio_data[0].second == 1);



 }


 TEST_CASE("cut, STEREO",""){
 	std::vector<std::pair<int8_t,int8_t>> v_audio3;
 	std::vector<std::pair<int8_t,int8_t>> v_audio4;

 	for(int i=1;i<6;i++){
 	v_audio3.push_back(std::make_pair(i,i+1));
 	v_audio4.push_back(std::make_pair(i+1,i+2));
 	}

 	audio<int8_t,std::pair<int8_t,int8_t>> aud1(v_audio3);

 aud1^std::pair<int,int>(0,1);// works

 REQUIRE(aud1.audio_data.size()==3);
REQUIRE(aud1.audio_data[0].first == 3);
 REQUIRE(aud1.audio_data[0].second ==4);




 }

 TEST_CASE("REVERSE, STEREO",""){
 	std::vector<std::pair<int8_t,int8_t>> v_audio3;
 	std::vector<std::pair<int8_t,int8_t>> v_audio4;

 	for(int i=1;i<6;i++){
 	v_audio3.push_back(std::make_pair(i,i+1));
 	v_audio4.push_back(std::make_pair(i+1,i+2));
 	}

 	audio<int8_t,std::pair<int8_t,int8_t>> aud4(v_audio3);
 aud4.reverse();

 REQUIRE(aud4.audio_data.size()==5);
 REQUIRE(aud4.audio_data[0].first == 5);
 REQUIRE(aud4.audio_data[0].second == 6);

 }

TEST_CASE("RANGE ADD, STEREO",""){
    std::vector<std::pair<int8_t,int8_t>> v_audio3;
    std::vector<std::pair<int8_t,int8_t>> v_audio4;

    for(int i=1;i<6;i++){
        v_audio3.push_back(std::make_pair(i,i+1));
        v_audio4.push_back(std::make_pair(i+1,i+2));
    }

    std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
    std::vector<int16_t> v_aud2 = {2, 4, -10, 127, -128};

    audio<int16_t,int16_t> aud3(v_aud1);
    audio<int16_t, int16_t> aud4(v_aud2);

    audio<int16_t,int16_t>::rangedAdd rAdd;//function object
    audio<int16_t,int16_t> range_sum = rAdd(aud3,0,3,aud4,0,3);

    REQUIRE(range_sum.audio_data[0]==3);
    REQUIRE(range_sum.audio_data[1] == 5);
    REQUIRE(range_sum.audio_data[2]==-9);
    REQUIRE(range_sum.audio_data[3] == 127);

}

TEST_CASE("COMPUTE RMS, STEREO",""){

    std::vector<std::pair<int8_t,int8_t>> v_audio3;
    std::vector<std::pair<int8_t,int8_t>> v_audio4;

    for(int i=1;i<6;i++){
        v_audio3.push_back(std::make_pair(i,i+1));
        v_audio4.push_back(std::make_pair(i+1,i+2));
    }




    std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
    std::vector<int16_t> v_aud2 = {1, 1, 1, 1, 1};


    audio<int16_t,int16_t> aud3(v_aud1);
    audio<int16_t, int16_t> aud4(v_aud2);

    aud3.rms_cal();
    aud4.rms_cal();
    REQUIRE(aud3.rms<2);
    REQUIRE(aud4.rms==1.0);

}

TEST_CASE("NORMALISE, STEREO","") {

    std::vector<std::pair<int8_t,int8_t>> v_audio3;
    std::vector<std::pair<int8_t,int8_t>> v_audio4;

    for(int i=1;i<6;i++){
        v_audio3.push_back(std::make_pair(i,i+1));
        v_audio4.push_back(std::make_pair(i+1,i+2));
    }




    std::vector <int16_t> v_aud1 = {1, 1, 1, 3, -2};
    std::vector <int16_t> v_aud2 = {1, 1, 1, 1, 1};


    audio < int16_t, int16_t > aud3(v_aud1);
    audio < int16_t, int16_t > aud4(v_aud2);

    aud3.rms_cal();
    aud4.rms_cal();
    REQUIRE(aud3.rms < 2);
    REQUIRE(aud4.rms == 1.0);
}








/************* TESTS FOR MONO *****************/
/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////


 TEST_CASE("AUDIO CONCATNATION, MONO",""){
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



 TEST_CASE("VOLUME FACTOR, MONO",""){
   std::vector<int8_t> v_aud1 = {1, 1, 1, 1,-1};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 100, -40};

 audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 // audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);
 aud4*std::pair<float,float>(0.5,0.5);
 aud1*std::pair<float,float>(0.1,0.5);

 REQUIRE(aud4.audio_data[0]==1);
 REQUIRE(aud4.audio_data[1] == 2);
 REQUIRE(aud4.audio_data[2] == -5);
 REQUIRE(aud4.audio_data[3] == 50);
 REQUIRE(aud4.audio_data[4] == -20);
 // REQUIRE(sum.audio_data[5] == 3);


 }

 TEST_CASE("SOUND AMPLITUDE ADDITION PER SAMPLE, MONO",""){
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


 TEST_CASE("CUT IMPLEMENTATION, MONO",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {2, 4, -10, 127, -128};

 // audio<int8_t,int8_t> aud1(v_aud1);
 // audio<int8_t, int8_t> aud2(v_aud2);
 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);
 // audio<int16_t,int16_t> sum1 = aud3+aud4;
 aud4 ^ std::pair<int, int>(0, 1);



 REQUIRE(aud4.audio_data.size()==3);
 REQUIRE(aud4.audio_data[0]==-10);
 REQUIRE(aud4.audio_data[1] == 127);
 }


 TEST_CASE("REVERSE, MONO",""){
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

 TEST_CASE("RANGE ADD, MONO",""){
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

 TEST_CASE("COMPUTE RMS, MONO",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {1, 1, 1, 1, 1};


 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);

 aud3.rms_cal();
 aud4.rms_cal();
 REQUIRE(aud3.rms<2);
 REQUIRE(aud4.rms==1.0);

 }

 TEST_CASE("NORMALISE, MONO",""){
   std::vector<int16_t> v_aud1 = {1, 1, 1, 3,-2};
 std::vector<int16_t> v_aud2 = {1, 1, 1, 1, 1};


 audio<int16_t,int16_t> aud3(v_aud1);
 audio<int16_t, int16_t> aud4(v_aud2);

 aud3.rms_cal();
 aud4.rms_cal();
 REQUIRE(aud3.rms<2);
 REQUIRE(aud4.rms==1.0);
}