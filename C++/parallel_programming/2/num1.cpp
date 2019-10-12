#include<iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <cassert>
#include<chrono>
#include<string>
#include<type_traits>
#include<cstdint>

class Foo{
public:
	int a;
	explicit Foo (int x){a=x;} 
	explicit operator int(){ 
		return a;
	}
};
typedef Foo foo;

class Bar {
public:
	int a;
	Bar(int x){a=x;}
	operator int(){ 
		return  a;
	}
};
typedef Bar bar;

int main (int argc, char **argv){
std::cout<<std::boolalpha;
//std::cout<<std::is_same<Foo, foo_type>::value<<std::endl;
std::cout << "foo(int): " << std::is_constructible<foo,int>::value << std::endl;
std::cout << "foo(int *): " << std::is_constructible<foo,int*>::value << std::endl;
std::cout << "bar(int): " << std::is_constructible<bar,int>::value << std::endl;
std::cout << "From foo to int: " << std::is_convertible<foo, int>::value << std::endl;
std::cout << "From bar to int: " << std::is_convertible<bar, int>::value << std::endl;
std::cout << "From int to foo: " << std::is_convertible<int, foo>::value << std::endl;
std::cout << "From int to bar: " << std::is_convertible<int, bar>::value << std::endl;
/*Вывод:
foo(int): true
foo(int *): false
bar(int): true
From foo to int: false
From bar to int: true
From int to foo: false
From int to bar: true
is_constructible< class T, class... Args > возвращает true, если T можно "сконструировать" с помощью набора аргументов class... Args (причем конструктор может быть как explicit, так и не-explicit), в противном случае is_constructible<…> возвращает false.
is_convertible< class From, class To > возвращает true, если From может быть приведен к To с помощью неявного преобразования (не-explicit). Таким образом, если используются явные (explicit) конструкторы и нужно узнать, получится ли экземпляр класса X на основе экземпляра класса Y, следует использовать is_constructible, если используются неявные, можно использовать как is_convertible, так и is_constructible. 
*/
return 0;
}
