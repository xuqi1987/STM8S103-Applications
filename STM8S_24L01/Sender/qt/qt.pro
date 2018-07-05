TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH=../FWLIB/inc/

HEADERS += \
    ../FWLIB/inc/stm8s.h \
    ../FWLIB/inc/stm8s_adc1.h \
    ../FWLIB/inc/stm8s_adc2.h \
    ../FWLIB/inc/stm8s_awu.h \
    ../FWLIB/inc/stm8s_beep.h \
    ../FWLIB/inc/stm8s_can.h \
    ../FWLIB/inc/stm8s_clk.h \
    ../FWLIB/inc/stm8s_exti.h \
    ../FWLIB/inc/stm8s_flash.h \
    ../FWLIB/inc/stm8s_gpio.h \
    ../FWLIB/inc/stm8s_i2c.h \
    ../FWLIB/inc/stm8s_itc.h \
    ../FWLIB/inc/stm8s_iwdg.h \
    ../FWLIB/inc/stm8s_rst.h \
    ../FWLIB/inc/stm8s_spi.h \
    ../FWLIB/inc/stm8s_tim1.h \
    ../FWLIB/inc/stm8s_tim2.h \
    ../FWLIB/inc/stm8s_tim3.h \
    ../FWLIB/inc/stm8s_tim4.h \
    ../FWLIB/inc/stm8s_tim5.h \
    ../FWLIB/inc/stm8s_tim6.h \
    ../FWLIB/inc/stm8s_uart1.h \
    ../FWLIB/inc/stm8s_uart2.h \
    ../FWLIB/inc/stm8s_uart3.h \
    ../FWLIB/inc/stm8s_uart4.h \
    ../FWLIB/inc/stm8s_wwdg.h \
    ../USER/nRF24L01.h \
    ../USER/stm8s_conf.h \
    ../USER/stm8s_it.h

SOURCES += \
    ../FWLIB/src/stm8s_adc1.c \
    ../FWLIB/src/stm8s_adc2.c \
    ../FWLIB/src/stm8s_awu.c \
    ../FWLIB/src/stm8s_beep.c \
    ../FWLIB/src/stm8s_can.c \
    ../FWLIB/src/stm8s_clk.c \
    ../FWLIB/src/stm8s_exti.c \
    ../FWLIB/src/stm8s_flash.c \
    ../FWLIB/src/stm8s_gpio.c \
    ../FWLIB/src/stm8s_i2c.c \
    ../FWLIB/src/stm8s_itc.c \
    ../FWLIB/src/stm8s_iwdg.c \
    ../FWLIB/src/stm8s_rst.c \
    ../FWLIB/src/stm8s_spi.c \
    ../FWLIB/src/stm8s_tim1.c \
    ../FWLIB/src/stm8s_tim2.c \
    ../FWLIB/src/stm8s_tim3.c \
    ../FWLIB/src/stm8s_tim4.c \
    ../FWLIB/src/stm8s_tim5.c \
    ../FWLIB/src/stm8s_tim6.c \
    ../FWLIB/src/stm8s_uart1.c \
    ../FWLIB/src/stm8s_uart2.c \
    ../FWLIB/src/stm8s_uart3.c \
    ../FWLIB/src/stm8s_uart4.c \
    ../FWLIB/src/stm8s_wwdg.c \
    ../USER/main.c \
    ../USER/nRF24L01.c \
    ../USER/stm8s_it.c
