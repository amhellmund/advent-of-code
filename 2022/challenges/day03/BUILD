cc_library(
    name = "rucksack",
    srcs = ["rucksack.cpp"],
    hdrs = ["rucksack.hpp"],
    visibility = [
        "//visibility:public"
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":rucksack"
    ]
)