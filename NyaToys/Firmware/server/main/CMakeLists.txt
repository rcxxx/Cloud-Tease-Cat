idf_component_register(SRCS  "main.c"
                        "RPCProtocol/RPCProtocol_ll_esp32now.c"
                        "RPCProtocol/RPCProtocol_ll_esp32uart.c"
                    INCLUDE_DIRS "." "RPCProtocol")