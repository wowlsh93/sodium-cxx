#include <sodium/sodium.h>
#include <sodium/router.h>

struct Context
{
    Context(int value_) : value(value_) {}
    Context(const Context& ctx) : value(ctx.value) {}
    ~Context() {}
    int value;
};

void dump(int x)
{
}

int main(int argc, char* argv[])
{
    sodium::stream_sink<int> value;
    sodium::router<int, int> valueR(value, [] (const int& x) { return x; });

    Context ctx(99);
    auto l = valueR
            .filter_equals(3)
            .map([ctx] (int x) { return x + ctx.value; })
            .listen([ctx] (int x) {
        dump(x+ctx.value);
    });

    for (int i = 0; i < 1000000; i++)
        value.send(3);

    l();
}
