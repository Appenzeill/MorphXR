#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "../src/toolbox.hpp"
#include "ostream"

TEST_CASE( "Check of de toolbox graden omzet naar pixels voor het oled scherm." ){
  toolbox v;
  REQUIRE( v.translateToScreenSize(200)  == 66 );
  REQUIRE( v.translateToScreenSize(180)  == 60 );
  REQUIRE( v.translateToScreenSize(90)   == 30 );
  REQUIRE( v.translateToScreenSize(60)   == 20 );
  REQUIRE( v.translateToScreenSize(40.5) == 13 );
  REQUIRE( v.translateToScreenSize(20)   == 6  );
  REQUIRE( v.translateToScreenSize(10)   == 3  );
  REQUIRE( v.translateToScreenSize(-10)  == -3 );
}

TEST_CASE( "Check of het verschil tussen 2 waarden klopt." ){
  toolbox v;
  REQUIRE( v.difference(10,5) == 5 );
  REQUIRE( v.difference(8,5)  == 3 );
  REQUIRE( v.difference(5,3)  == 2 );
  REQUIRE( v.difference(4,1)  == 3 );
  REQUIRE( v.difference(3,-3) == 6 );
  REQUIRE( v.difference(2,-4) == 6 );
  REQUIRE( v.difference(-4,5) == -9 );
  REQUIRE( v.difference(8,9)  == -1 );
}

TEST_CASE( "Check of het de stappen voor de led klopt" ){
  toolbox v;
  REQUIRE( v.steps(30,1) == 30 );
  REQUIRE( v.steps(30,2) == 15 );
  REQUIRE( v.steps(30,3) == 10 );
  REQUIRE( v.steps(30,4) == 7 );
  REQUIRE( v.steps(30,5) == 6 );
  REQUIRE( v.steps(30,6) == 5 );
  REQUIRE( v.steps(30,7) == 4 );
  REQUIRE( v.steps(30,8) == 3 );
}
