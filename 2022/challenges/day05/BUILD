cc_library(
    name = "crates",
    srcs = ["crates.cpp"],
    hdrs = ["crates.hpp"],
    copts = ["-g"],
    visibility = [
        "//visibility:public"
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    copts = ["-g"],
    deps = [
        ":crates"
    ]
)