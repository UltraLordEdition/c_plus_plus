#include "stdafx.h"
#include "tests.h"

//Implementation

void TestAddSynonyms()
{
    {
        Synonyms empty;
        //Создали синонимы
        AddSynomyns(empty, "a", "b");
        //Ожидаем от функции
        const Synonyms expected = {
            { "a",{ "b" } },
            { "b",{ "a" } },
        };
        //Формируем наши ожидания используя assert
        AssertEqual(empty, expected, "Add to empty");
    }
    {
        Synonyms synonyms = {
            { "a",{ "b" } },
            { "b",{ "a", "c" } },
            { "c",{ "b" } }
        };
        AddSynomyns(synonyms, "a", "c");
        const Synonyms expected = {
            { "a",{ "b", "c" } },
            { "b",{ "a", "c" } },
            { "c",{ "b", "a" } }
        };
        AssertEqual(synonyms, expected, "Add to non-empty");
    }
}

void TestCount()
{

    {
        Synonyms empty;
        //Добавим уникальную строчку Hint для идентификации сработавшего assert
        //Укажем что второй параметр безнаковый "u" т.к. идет сравнение безнакового со знаковым типом
        AssertEqual(GetSynonymCount(empty, "a"), 0u, "count for empty");
    }

    {
        Synonyms synonyms = {
            { "a",{ "b", "c" } },
            { "b",{ "a" } },
            { "c",{ "a" } }
        };
        AssertEqual(GetSynonymCount(synonyms, "a"), 2u, "count for a");
        AssertEqual(GetSynonymCount(synonyms, "b"), 1u, "count for b");
        AssertEqual(GetSynonymCount(synonyms, "z"), 0u, "count for z");
    }
}
//Поправим код здесь
void TestAreSynonyms()
{
    {
        Synonyms empty;
        Assert(!AreSynonyms(empty, "a", "b"), "empty a b");
        Assert(!AreSynonyms(empty, "b", "a"), "empty b a");
    }
    {
        Synonyms synonyms = {
            { "a",{ "b", "c" } },
            { "b",{ "a" } },
            { "c",{ "a" } }
        };
        Assert(AreSynonyms(synonyms, "a", "b"), "empty a b");
        Assert(AreSynonyms(synonyms, "b", "a"), "empty b a");
        Assert(AreSynonyms(synonyms, "a", "c"), "empty a c");
        Assert(AreSynonyms(synonyms, "c", "a"), "empty c a");
        Assert(!AreSynonyms(synonyms, "b", "c"), "empty b c");
        Assert(!AreSynonyms(synonyms, "c", "b"), "empty c b");
    }
}
//используем фунцию TestAll, чтобы деструктор выполнялся после всех тестов
// а не в конце функции main
void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestAreSynonyms, "TestAreSynonyms");
    tr.RunTest(TestCount, "TestCount");
    tr.RunTest(TestAddSynonyms, "TestAddSynonyms");
    //дальше объект tr класса TestRunner будет разрушаться
    //функция закончилась и не какие тесты больше не будут вызываться
    //поэтому анализ переменной fail_count поместим в деструктор класса TestRunner
}