cc_library(
    name = "cleanup",
    srcs = ["cleanup.cpp"],
    hdrs = ["cleanup.hpp"],
    visibility = [
        "//visibility:public"
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":cleanup"
    ]
)