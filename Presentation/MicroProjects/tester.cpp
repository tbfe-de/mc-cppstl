#include <algorithm>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <vector>
#include <tuple>

#define P(v, x) \
    do { std::ostringstream s, t; \
         s << (v); t << (x); \
         if  (std::strcmp(s.str().c_str(), t.str().c_str())) {\
             std::cout << "| " #v " --> " << s.str() \
                       << " != " << t.str() << " <--"; \
             std::string::size_type i = 0; \
             while (i < s.str().length() \
                 && i < t.str().length() \
                 && s.str().at(i) == t.str().at(i)) ++i; \
              std::cout << " chr: " << i << " (" \
                        << (i < s.str().length() ? int(s.str().at(i)) : '?') << ':' \
                        << (i < t.str().length() ? int(t.str().at(i)) : '?') << ")\n"; \
         } \
    } while (0)

int a = 7; int b = 12;

template<typename T>
class IN {
    std::istringstream iss;
public:
    std::istream_iterator<T> operator()() {
        return {};
    }
    std::istream_iterator<T> operator()(const std::string &s) {
        iss.clear();
        iss.str(s);
        return {iss};
    }
};


template<typename T>
class OUT {
    std::ostringstream oss;
public:
    std::ostream_iterator<T> operator()(const char *sep = " ") {
        oss.seekp(0);
        return {oss, sep};
    }
    std::string operator*() {
        oss << std::ends;
        return oss.str();
    }
    friend std::ostream &operator<<(std::ostream &lhs, OUT &rhs) {
        rhs.oss << std::ends;
        return lhs << rhs.oss.str();
    }
    
};

class TST {
    static int count;
    static TST done;
    bool byebye = false;
    TST() : byebye(true) {};
public:
    TST(const char *t, std::function<void()> f) {
        if (t[0] != '+') return;
        std::cout << t << '\n';
        try {
            ++count;
            f();
        }
        catch(std::exception &e) {
            std::cout << "!\n!!! terminated by '" << e.what() << "'\n";
        }
        catch(...) {
            std::cout << "!\n!!! terminated by non-standard exception\n";
        }
        std::cout << '+' << std::endl;
    }
    ~TST() {
        if (byebye)
            std::cout << "$<" << count << ">$\n" << std::flush;
    }
};
int TST::count{0};
TST TST::done;
    

IN<int> issi;
OUT<int> ossi;

int main() {
    using namespace std;
    std::cout.setf(ios::boolalpha);
    
    TST("-------------------------------- test throwing exception", []() {

        throw std::logic_error("logic error thrown");

    });

    TST("+------------------------------------ std::copy algorithm", []() {

        copy(issi("5 9 12 8"), issi(), ossi());

        P(ossi, "5 9 12 8 ");
    });
    
    TST("+------------------------------------ std::minmax_element", []() {

        auto minmax_it = std::minmax_element(issi("3 5 1 -1 7 9 12"), issi());

        P(minmax_it.first == issi()  , false);
        P(minmax_it.second == issi() , false);
        P(*minmax_it.first           , -1   );
        P(*minmax_it.second          , 12   );
    });
    
    TST("+---------------------------- std::minmax_element (empty)", []() {

        auto minmax_it2 = std::minmax_element(issi(""), issi());

        P(minmax_it2.first == issi() , true);
        P(minmax_it2.second == issi(), true);
    });
}

