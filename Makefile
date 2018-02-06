HAL_FILES = $(shell plpfiles copy --item=hal_files)

HAL_FILES += hal/pulp.h hal/pulp_io.h hal/debug_bridge/debug_bridge.h

INSTALL_FILES += $(foreach file,$(HAL_FILES),include/$(file))

WS_INSTALL_FILES += $(INSTALL_FILES)

include $(PULP_SDK_HOME)/install/rules/pulp.mk
