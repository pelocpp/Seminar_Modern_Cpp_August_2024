// ========================================================================
// VariadicTemplate_01_Introduction.cpp // Variadic Templates: Introduction
// ========================================================================

module modern_cpp:variadic_templates;

namespace VariadicTemplates_Seminar {

    // C++ 11

    // non variadic
    //template <typename T>
    //void printer(T n)
    //{
    //    std::cout << n << std::endl;
    //}

    void printer()
    {
        std::cout << "bin hier" << std::endl;
    }

    // variadic
    template <typename T, typename ... TArgs> // einpacken
    void printer(T n, TArgs ... args)            // einpacken
    {
        std::cout << n << std::endl;

        printer(args ... );                  // auspacken
    }

    // --------------------------

    // C++ 20 
    void printer1()
    {
    }

    // variadic
    void printer1(auto n, auto ... args)
    {
        std::cout << n << std::endl;

        printer1(args ...);
    }

    // -------------------------------

    // C++ 17

    // variadic
    template <typename T, typename ... TArgs>     // einpacken
    void printer2(T n, TArgs ... args)            // einpacken
    {
        std::cout << n << std::endl;

        if constexpr (sizeof ... (args) > 0) {

            printer2(args ...);                  // auspacken
        }
    }


    // -------------------------------

    // C++ 20

    // variadic
    void printer3(auto n, auto ... args)            // einpacken
    {
        std::cout << n << std::endl;

        if constexpr ( sizeof ... (args) > 0 ) {

            printer3(args ...);                  // auspacken
        }
    }

    // -------------------------------

    // C++ 20

    // variadic
    void printer4( auto ... args )            // einpacken
    {
        std::cout << "printer4:" << std::endl;

        std::initializer_list<int> list { args ... };

        // range-based loop
        for ( auto n : list) {

            std::cout << n << std::endl;
        }
    }

    void printer5(auto first, auto ... args)            // einpacken
    {
        std::cout << "printer5:" << std::endl;

        using Type = decltype(first);

        std::initializer_list<Type> list{ first, args ... };

        // range-based loop
        for (auto n : list) {

            std::cout << n << std::endl;
        }
    }

    void printer6(auto&& first, auto&& ... args)            // einpacken
    {
        std::cout << "printer6:" << std::endl;

        using Type = decltype(first);
        using TypeWORef = std::remove_reference<decltype(first)>::type;

        TypeWORef dummy{};

     //   dummy = std::move(first);

       // dummy = first;

        //std::initializer_list<TypeWORef> list{ 
        //    std::forward<Type>(first), 
        //    std::forward<Type>(args) ...
        //};

        std::cout << "stopper" << std::endl;

        //std::initializer_list<Type> list{ first, args ... };

        //// range-based loop
        //for (auto n : list) {

        //    std::cout << n << std::endl;
        //}
    }

    class X
    {
    public:
        X() = default;

        // non copy-able
        X(const X&) = delete;
        X& operator= (const X&) = delete;

        // moveable
        X (X&&) noexcept = default;
        X& operator= (X&&) noexcept = default;
    };

    void test_seminar()
    {
        static_assert (! std::is_copy_constructible<X>::value);

        static_assert (std::is_move_constructible<X>::value);

       const X x1{};
        X x2{};
        X x3{};

        int n = 123;

        printer6 (x1, x2, x3, X{});
    }

    // ========================================================

    class Unknown
    {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        Unknown() : m_var1{ -1 }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) : m_var1{ n }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(int n, int m) : m_var1{ n }, m_var2{ m }, m_var3{ -1 } {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) : m_var1{ n }, m_var2{ m }, m_var3{ k } {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }
    };

    template <typename T, typename ... TArgs>
    std::unique_ptr <T> my_make_unique(TArgs ... args)
    {
        std::unique_ptr <T> tmp{ new T{ args ... } };
        return tmp;
    }

    template <typename T, typename ... TArgs>
    std::unique_ptr <T> my_make_uniqueEx(TArgs&& ... args)
    {
        std::unique_ptr <T> tmp{ new T{ std::forward<TArgs>(args) ... } };
        return tmp;
    }

    void test_seminar_02()
    {
        std::unique_ptr <Unknown> up = std::make_unique<Unknown>( 1, 2, 3 );
    
        std::unique_ptr <Unknown> up2 = my_make_uniqueEx<Unknown, int, int, int>(1, 2, 3);
    }
}

namespace VariadicTemplatesIntro_01 {

    // ====================================================================
    // 1. Beispiel für ein variadisches Template:
    // Eine print-Funktion mit beliebig vielen Argumenten
    // ====================================================================

    // Non-recursive template part (regular template)
    template <typename T>
    void print(T value)
    {
        std::cout << value << " ";
    }

    // Recursive template part
    template <typename T, typename ... TRest>
    void print(T n, TRest ... rest)
    {
        print<T>(n);
        print<TRest...>(rest ...);
    }

    static void test_printer_01()
    {
        print<int, int, int, int, int>(1, 2, 3, 4, 5);
    }
}

namespace VariadicTemplates_TestClassUnknown {

    // ========================================================================
    // Test-Klasse Unknown
    // Nur die Konstruktoren sind interessant
    // ========================================================================

    class Unknown
    {
    private:
        int m_var1;
        int m_var2;
        int m_var3;

    public:
        Unknown() : m_var1{ -1 }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor()" << std::endl;
        }

        Unknown(int n) : m_var1{ n }, m_var2{ -1 }, m_var3{ -1 } {
            std::cout << "c'tor(int)" << std::endl;
        }

        Unknown(int n, int m) : m_var1{ n }, m_var2{ m }, m_var3{ -1 } {
            std::cout << "c'tor(int, int)" << std::endl;
        }

        Unknown(int n, int m, int k) : m_var1{ n }, m_var2{ m }, m_var3{ k } {
            std::cout << "c'tor(int, int, int)" << std::endl;
        }

        friend std::ostream& operator<< (std::ostream&, const Unknown&);
    };

    std::ostream& operator<< (std::ostream& os, const Unknown& obj) {
        os 
            << "var1: " << obj.m_var1
            << ", var2: " << obj.m_var2
            << ", var3: " << obj.m_var3 << std::endl;

        return os;
    }
}

namespace VariadicTemplatesIntro_02 {

    // =============================================================
    // 2. Beispiel für ein variadisches Template:
    // Anwendungsfall: Standardfunktion std::unique_ptr<>
    // =============================================================

    using namespace VariadicTemplates_TestClassUnknown;

    // einfache Variante
    template<typename T, typename... TArgs>
    std::unique_ptr<T> my_make_unique(TArgs... args)
    {
        return std::unique_ptr<T>{ new T{ args... } };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename... TArgs>
    std::unique_ptr<T> my_make_unique_ex(TArgs&&... args)
    {
        return std::unique_ptr<T>{ new T{ std::forward<TArgs>(args)... } };
    }

    static void test_my_make_unique()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique<Unknown>(n, m);
    }

    static void test_my_make_unique_ex()
    {
        std::unique_ptr<Unknown> up1 = my_make_unique_ex<Unknown>();
        std::unique_ptr<Unknown> up2 = my_make_unique_ex<Unknown>(1);
        std::unique_ptr<Unknown> up3 = my_make_unique_ex<Unknown>(10, 11);
        std::unique_ptr<Unknown> up4 = my_make_unique_ex<Unknown>(100, 101, 102);

        int n = 33, m = 34;
        std::unique_ptr<Unknown> up5 = my_make_unique_ex<Unknown>(n, m);
    }
}

namespace VariadicTemplatesIntro_03 {

    // =============================================================
    // 3. Beispiel für ein variadisches Template:
    // Anwendungsfall: Zugriff auf die einzelnen Elemente eines Parameter Packs
    // =============================================================

    template <typename... TArgs>
    void func(TArgs... args) {

        // unpack all function arguments with the help of a std::initializer_list object
        auto unpackedArgs = { args ... };

        for (auto param : unpackedArgs) {
            std::cout << "Passed Argument: " << param << std::endl;
        }
    }

    static void test_accessing_parameterpack()
    {
        func(10, 11, 12, 13, 14, 15);
    }
}

namespace VariadicTemplatesIntro_04 {

    // =================================================================================
    // 4. Beispiel für ein variadisches Template:
    // 
    // Anwendungsfall: "Generische Funktion 'make_an_object'"
    //                 Umsetzung Parameter Pack auf einen passenden Konstruktor
    // 
    // Siehe Analogien zu Factory-Pattern
    // =================================================================================

    using namespace VariadicTemplates_TestClassUnknown;

    // einfache Variante
    template<typename T, typename... TArgs>
    T make_an_object(const TArgs&... args)
    {
        return T{ args... };
    }

    // bessere Variante: Mit Universal Referenz
    template<typename T, typename... TArgs>
    T make_an_object_ex(TArgs&&... args)
    {
        return T{ std::forward<TArgs>(args)... };
    }

    static void test_make_an_object()
    {
        Unknown u1 = make_an_object<Unknown>();
        Unknown u2 = make_an_object<Unknown>(1);
        Unknown u3 = make_an_object<Unknown>(10, 11);
        Unknown u4 = make_an_object<Unknown>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        Unknown u5 = make_an_object<Unknown, int, int&, const int&>(100, n, m);
        Unknown u6 = make_an_object<Unknown>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;

        // doesn't compile: too much parameters
        // Unknown u7 = make_an_object<Unknown>(1000, 1001, 1002, 1003);
        // std::cout << u7 << std::endl;
    }

    static void test_make_an_object_ex()
    {
        Unknown u1 = make_an_object_ex<Unknown>();
        Unknown u2 = make_an_object_ex<Unknown>(1);
        Unknown u3 = make_an_object_ex<Unknown>(10, 11);
        Unknown u4 = make_an_object_ex<Unknown>(100, 101, 102);

        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;
        std::cout << u3 << std::endl;
        std::cout << u4 << std::endl;

        int n = 100;
        const int m = 101;

        Unknown u5 = make_an_object_ex<Unknown, int, int&, const int&>(100, n, m);
        Unknown u6 = make_an_object_ex<Unknown>(n, 51, m);

        std::cout << u5 << std::endl;
        std::cout << u6 << std::endl;
    }
}

namespace VariadicTemplatesIntro_05 {

    // ========================================================================
    // 5.) Drittes Beispiel:
    // Ein variadisches Template in zwei Realisierungsvarianten.
    // 
    // Ende der Rekursion:
    // a) Eine rekursive Template Funktion
    // b) Eine nicht-rekursive Non-Template Funktion
    // 
    // Man beachte: Wenn sich zwei Template Funktionen nur um das Parameter Pack
    // unterscheiden, wird - wenn möglich - die Template Funktionen ohne Parameter Pack bevorzugt:
    // ========================================================================

    // Ende der Rekursion: Eine non-Template Funktion
    static void print()
    {
    }

    template<typename T, typename... Types>
    void print(T firstArg, Types... args)
    {
        std::cout << firstArg << std::endl; // print first argument
        print(args...); // call print() for remaining arguments
    }

    // Oder:
    // Ende der Rekursion: Eine Template Funktion

    template<typename T>
    void printEx(T arg)
    {
        std::cout << arg << std::endl; // print passed argument
    }

    template<typename T, typename... Types>
    void printEx(T firstArg, Types... args)
    {
        printEx(firstArg); // call print() for first argument
        printEx(args...);  // call print() for remaining arguments
    }

    static void test_printer_02()
    {
        print(123.456, "Hello", 789);
        print<double, const char*, int>(123.456, "Hello", 789);

        printEx(123.456, "Hello", 789);
        printEx<double, const char*, int>(123.456, "Hello", 789);
    }
}


void main_variadic_templates_introduction()
{
    using namespace VariadicTemplates_Seminar;
    test_seminar();
    return;

    using namespace VariadicTemplatesIntro_01;
    test_printer_01();

    using namespace VariadicTemplatesIntro_02;
    test_my_make_unique();
    test_my_make_unique_ex();

    using namespace VariadicTemplatesIntro_03;
    test_accessing_parameterpack();

    using namespace VariadicTemplatesIntro_04;
    test_make_an_object();
    test_make_an_object_ex();

    using namespace VariadicTemplatesIntro_05;
    test_printer_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
