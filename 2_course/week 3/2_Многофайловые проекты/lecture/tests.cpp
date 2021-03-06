#include "stdafx.h"
#include "tests.h"

//Implementation

void TestAddSynonyms()
{
    {
        Synonyms empty;
        //������� ��������
        AddSynomyns(empty, "a", "b");
        //������� �� �������
        const Synonyms expected = {
            { "a",{ "b" } },
            { "b",{ "a" } },
        };
        //��������� ���� �������� ��������� assert
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
        //������� ���������� ������� Hint ��� ������������� ������������ assert
        //������ ��� ������ �������� ���������� "u" �.�. ���� ��������� ����������� �� �������� �����
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
//�������� ��� �����
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
//���������� ������ TestAll, ����� ���������� ���������� ����� ���� ������
// � �� � ����� ������� main
void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestAreSynonyms, "TestAreSynonyms");
    tr.RunTest(TestCount, "TestCount");
    tr.RunTest(TestAddSynonyms, "TestAddSynonyms");
    //������ ������ tr ������ TestRunner ����� �����������
    //������� ����������� � �� ����� ����� ������ �� ����� ����������
    //������� ������ ���������� fail_count �������� � ���������� ������ TestRunner
}