/*

GCC
//In GCC, C++20 modules are totally broken and unusable, don't waste time
g++-11 -std=c++20 -fmodules-ts -Wall -c -xc++ unicode.ixx
g++-11 -std=c++20 -fmodules-ts -Wall -c -xc++ pretty-impl.ixx
g++-11 -std=c++20 -fmodules-ts -Wall -c -xc++ pretty.ixx
g++-11 -std=c++20 -fmodules-ts -Wall -c main.cpp
g++-11 -std=c++20 -fmodules-ts -Wall unicode.o pretty-impl.o pretty.o main.o

Clang
clang++-15 -std=c++20 -Wall -O3 -fprebuilt-module-path=. -xc++-module unicode.ixx pretty-impl.ixx pretty.ixx --precompile
clang++-15 -std=c++20 -Wall -O3 -s -fprebuilt-module-path=. main.cpp unicode.pcm pretty-impl.pcm pretty.pcm

*/

//#include <format>
#include <iostream>
#include <string>

#if defined(_MSC_VER) && !defined(CMAKE)
import pretty;
#else
#include "pretty.h"
#endif

using std::cout;

void TableTests()
{
	{
		const auto table = pretty::Table()
			.addRow("Country",
					"UN Region",
					"Estimate:IMF",
					"Year",
					"Estimate:World Bank",
					"Year")
			.addRow("World", "-", "101,560,901", "2022", "96,513,077", "2021")
			.addRow("United States", "Americas", "25,035,164", "2022", "22,996,100", "2021")
			.addRow("China", "Asia", "18,321,197", "2022", "17,734,063", "2021")
			.addRow("Japan", "Asia", "4,300,621", "2022", "4,937,422", "2021")
			.addRow("Germany", "Europe", "4,031,149", "2022", "4,223,116", "2021")
			.addRow("India", "Asia", "3,468,566", "2022", "3,173,398", "2021")
			.addRow("United Kingdom", "Europe", "3,198,470", "2022", "3,186,860", "2021");
		
		pretty::Printer print;
		cout << print(table);
	}
	{
		const auto table = pretty::Table()
			.addCol({
				"Country",
				"World",
				"United States",
				"China",
				"Japan",
				"Germany",
				"India",
				"United Kingdom"})
			.addCol({
				"UN Region",
				"-",
				"Americas",
				"Asia",
				"Asia",
				"Europe",
				"Asia",
				"Europe"})
			.addRow("France","Europe");

		pretty::Printer print;
		print.frame(pretty::FrameStyle::Basic);
		cout << print(table);

		print.frame(pretty::FrameStyle::Line);
		cout << print(table);

		print.frame(pretty::FrameStyle::LineRounded);
		cout << print(table);

		print.frame(pretty::FrameStyle::ThickLine);
		cout << print(table);

		print.frame(pretty::FrameStyle::DoubleLine);
		cout << print(table);

		print.frame(pretty::FrameStyle::Minimal);
		cout << print(table);

		print.frame(pretty::FrameStyle::Line);
		print.padding(0);
		cout << print(table);

		print.headerSeparator(false);
		cout << print(table);
	}
	{
		auto table = pretty::Table()
			.addColumns(3)
			.addRows(2);

		pretty::Printer print;
		print.headerSeparator(false);

		auto format = [](pretty::RowN r, pretty::ColN c)
		{
			return std::to_string(r.val()) + "," + std::to_string(c.val());
		};

		pretty::RowN r{};
		for (; r < table.numRows(); ++r)
			for (pretty::ColN c{}; c < table.numColumns(); ++c)
				table.setText(r, c, format(r, c));

		cout << print(table);

		table.addRows(3);
		for (;r < table.numRows(); ++r)
			for (pretty::ColN c{};c < table.numColumns(); ++c)
				table.setText(r, c, format(r, c));

		cout << print(table);
	}
	{
		pretty::Printer print;
		print.headerSeparator(false).padding(0);

		auto table = pretty::Table()
			.addRow("Afrikaans", "Hello Wêreld!");
		cout << print(table);

		table = pretty::Table()
			.addRow("Albanian", "Përshendetje Botë!");
		cout << print(table);

		table = pretty::Table()
			.addRow("Hungarian", "Helló Világ!");
		cout << print(table);

		table = pretty::Table()
			.addRow("Japanese", "こんにちは世界！");
		cout << print(table);

		table = pretty::Table()
			.addRow("Vietnamese", "Chào thế giới!");
		cout << print(table);

		table = pretty::Table()
			.addRow("Punjabi", "ਸਤਿ ਸ੍ਰੀ ਅਕਾਲ ਦੁਨਿਆ!");
		cout << print(table);

		table = pretty::Table()
			.addRow("Chinese", "你好世界！");
		cout << print(table);

		table = pretty::Table()
			.addRow("😃")
			.addRow("1");
		cout << print(table);

		table = pretty::Table()
			.addRow("💏")
			.addRow("2");
		cout << print(table);

		table = pretty::Table()
			.addRow("👨‍👩‍👦")
			.addRow("3");
		cout << print(table);	
	}
	{
		const auto table = pretty::Table()
			.addRow("r1")
			.addRow("r2")
			.addCol({ "c1", "c2" })
			.addRow("r3", "r3");

		pretty::Printer print;
		print.headerSeparator(false);
		cout << print(table);
	}
}

int main()
{
	TableTests();
}
