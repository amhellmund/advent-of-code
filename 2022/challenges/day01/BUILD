cc_library(
    name = "calory",
    srcs = ["calory.cpp"],
    hdrs = ["calory.hpp"],
    visibility = [
        "//visibility:public"
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":calory"
    ]
)

# cc_test(
#     name = "calory_test",
#     srcs = glob(["**/*.cpp"]),
#     deps = [
#         ":calory",
#         "@googletest//:gtest_main",
#     ],
# )