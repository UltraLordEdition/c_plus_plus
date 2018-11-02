#include "condition_parser.h"
#include "test_runner.h"
#include "database.h"

#include <sstream>
using namespace std;

void TestParseCondition() {
  {
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 1");
    Assert(!root->Evaluate({2017, 11, 18}, ""), "Parse condition 2");
  }
  {
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
    Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
  }
  {
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, ""), "Parse condition 5");
    Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
    Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
    Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
    Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
  }
  {
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
    Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
    Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
  }
  {
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
    Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
    Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
  }
  {
    istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 16");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 17");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2016, 1, 1}, "holiday"), "Parse condition 18");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 19");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 20");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 21");
  }
  {
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2016, 1, 1}, "event"), "Parse condition 22");
    Assert(root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 23");
    Assert(root->Evaluate({2017, 1, 2}, "workday"), "Parse condition 24");
    Assert(!root->Evaluate({2018, 1, 2}, "workday"), "Parse condition 25");
  }
  {
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 26");
    Assert(!root->Evaluate({2017, 1, 2}, "holiday"), "Parse condition 27");
  }
  {
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
    Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
    Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
  }
}

void TestParseDelete() {
  {
    Database db;
    db.Add({2017, 6, 1}, "1st of June");
    db.Add({2017, 7, 8}, "8th of July");
    db.Add({2017, 7, 8}, "Someone's birthday");   
  
    istringstream is("date == 2017-07-08");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
    };         
    AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 31");    
  }
  {
      Database db;
      db.Add({ 2017, 1, 1 }, "sport event");
      db.Add({ 2017, 1, 1 }, "holiday");
      
      istringstream is(R"(event == "sport event")");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 1, "Parse condition 32");
  }
  {
      Database db;
      db.Add({ 2016, 1, 1 }, "coffe");          //no
      db.Add({ 2017, 1, 1 }, "sport event");    //del
      db.Add({ 2017, 5, 1 }, "holiday");        //del
      db.Add({ 2017, 7, 1 }, "deadline");       //no
      db.Add({ 2017, 12, 25 }, "run");          //no

      istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 33");
  }
  {
      Database db;
      db.Add({ 2017, 1, 1 }, "sport event");
      db.Add({ 2017, 1, 1 }, "holiday");
      db.Add({ 2017, 1, 1 }, "Wednesday");
      
      istringstream is(R"(event != "sport event" AND event != "Wednesday")");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 1, "Parse condition 34");
  }
  {
      Database db;
      db.Add({ 2017, 11, 18 }, "sport event");
      db.Add({ 2017, 11, 18 }, "holiday");
      
      istringstream is(R"(event == "holiday AND date == 2017-11-18")");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 35");
  }
  {
      Database db;
      db.Add({ 2017, 11, 18 }, "sport event");
      db.Add({ 2017, 11, 18 }, "lunch");
      db.Add({ 2017, 11, 19 }, "holiday");
      db.Add({ 2017, 11, 19 }, "run");

      istringstream is(R"(event == "holiday AND date == 2017-11-18")");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 3, "Parse condition 36");
  }
  {
      Database db;
      db.Add({ 2017, 1, 1 }, "holiday");
      db.Add({ 2017, 1, 2 }, "holiday");
      
      istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 37");
  }
  {
      Database db;
      db.Add({ 2016, 1, 1 }, "holiday"); //no
      db.Add({ 2017, 1, 2 }, "holiday"); //del
      db.Add({ 2017, 1, 2 }, "workday"); //del
      db.Add({ 2018, 1, 2 }, "workday"); //no

      istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 38");
  }
  {
      Database db;
      db.Add({ 2016, 1, 1 }, "event");   //del
      db.Add({ 2017, 1, 2 }, "holiday"); //del
      db.Add({ 2017, 1, 2 }, "workday"); //del
      db.Add({ 2018, 1, 2 }, "workday"); //no

      istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 3, "Parse condition 39");
  }
  {
      Database db;
      db.Add({ 2017, 1, 1 }, "holiday"); //del
      db.Add({ 2017, 1, 2 }, "holiday"); //del
     
      istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 40");
  }
  {
      Database db;
      db.Add({ 1, 1, 1 }, "2017-01-01");  //del
      db.Add({ 2016, 1, 1 }, "event");    //no
      db.Add({ 2016, 1, 2 }, "event");    //del

      istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 41");
  }
  {
      Database db;
      db.Add({ 1, 1, 1 }, "2017-01-01");  //del
      db.Add({ 2016, 1, 1 }, "event");    //del
      db.Add({ 2016, 1, 2 }, "event");    //del

      istringstream is(R"(((event == "2017-01-01" OR date >= 2016-01-01)))");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 3, "Parse condition 42");
  }
  {
      Database db;
      db.Add({ 1, 1, 1 }, "2017-01-01");  //del
      db.Add({ 2016, 1, 1 }, "event");    //del
      db.Add({ 2016, 1, 2 }, "event");    //no

      istringstream is(R"(((event == "2017-01-01" OR date <= 2016-01-01)))");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
      };
      AssertEqual(db.RemoveIf(predicate), 2, "Parse condition 43");
  }  
}

void TestParseFind() {

}