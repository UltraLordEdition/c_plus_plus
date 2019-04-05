#include <string_view>
#include <string>
#include <list>
#include <iterator>
#include "test_runner.h"
#include "profile.h"
using namespace std;

//Статус курсора
enum class CursorStatus
{
    LEFT,
    RIGHT
};

class Editor {
 public:
    //Реализуйте конструктор по умолчанию и объявленные методы
    Editor() : pos_(str_.end()) {
    }

    //сдвинуть курсор влево
    void Left() {
        MoveCursor(CursorStatus::LEFT);
    }

    //сдвинуть курсор вправо
    void Right() {
        MoveCursor(CursorStatus::RIGHT);
    }

    //вставить символ token
    void Insert(char token) {
        str_.insert(getCursorPos(), token);
    }

    //вырезает не более tokens символов,
    //начиная с текущей позиции курсора
    void Cut(size_t tokens = 1) {
        list<char>::iterator next_pos = getCursorPos();

        //проверим не выходим ли мы за пределы str_
        int size = (distance(begin(str_), end(str_)) - distance(begin(str_), getCursorPos())) - static_cast<int>(tokens);
        if (size >= 0 ) {
            advance(next_pos, tokens);
        }
        else {
            next_pos = str_.end();
        }

        //копируем с текущей позиции курсора в буффер
        //но предварительно очистим буфер
        buff_.clear();
        buff_.splice(end(buff_), str_, getCursorPos(), next_pos);
        pos_ = next_pos;
    }

    //сопировать не более tokens символов, начиная с текущей позиции курсора
    void Copy(size_t tokens = 1) {
        list<char>::iterator next_pos = getCursorPos();

        //проверим не выходим ли мы за пределы str_
        int size = (distance(begin(str_), end(str_)) - distance(begin(str_), getCursorPos())) - static_cast<int>(tokens);
        if (size >= 0) {
            advance(next_pos, tokens);
        }
        else {
            next_pos = str_.end();
        }

        //копируем с текущей позиции курсора в буффер
        //но предварительно очистим буфер
        buff_.clear();
        buff_.insert(begin(buff_), getCursorPos(), next_pos);
    }

    //вставить содержимое буфера
    //в текущую позицию курсора
    void Paste() {
        //вставляем в строку содержимое буфера
        str_.insert(getCursorPos(), begin(buff_), end(buff_));
    }

    string GetText() const {
        string str;
        for (const auto& i : str_) {
            str.push_back(i);
        }
        return str;
    }

private:
    //контейнер для текста
    list<char> str_;
    //контейнер для вырезаного текста
    list<char> buff_;
    //начальная позиция курсора
    list<char>::iterator pos_;
    //получить позицию курсора
    list<char>::iterator& getCursorPos() {
        return pos_;
    }

    list<char>::iterator MoveCursor(CursorStatus status) {

        switch (status)
        {
            case CursorStatus::LEFT:
                if (begin(str_) != pos_) {
                    --pos_;
                }
                break;
            case CursorStatus::RIGHT:
                if (end(str_) != pos_) {
                    ++pos_;
                }
                break;
        default:
            break;
        }
        return pos_;
    }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  /*
  string str;
  { LOG_DURATION("string_add");
    for (int i = 0; i < 1'000'000; ++i) {
        str.push_back('a');
    }
  }
  { LOG_DURATION("string_erase");
    while(!str.empty()) {
        str.erase(0, 1);
    }
  }

  list<char> l;
  { LOG_DURATION("list_add");
    for (int i = 0; i < 1'000'000; ++i) {
        l.push_back('a');
    }
  }
  { LOG_DURATION("list_erase");
    while (!l.empty()) {
        l.erase(l.begin(), next(l.begin()));
    }
  }
  */
  /*
  list<char> l1 = { 'h','e','l','l','o',',',' ','w','o','r','l','d' };
  list<char> l2;

  auto it1 = l1.begin();
  auto it2 = l2.end();

  advance(it1, 7);

  l2.splice(it2, l1, it1, l1.end());
  */
  return 0;
}