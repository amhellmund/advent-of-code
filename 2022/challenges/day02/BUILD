cc_library(
    name = "rock_paper_scissor",
    srcs = ["rock_paper_scissor.cpp"],
    hdrs = ["rock_paper_scissor.hpp"],
    visibility = [
        "//visibility:public"
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":rock_paper_scissor"
    ]
)