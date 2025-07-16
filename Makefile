.PHONY: raylib-debug

raylib-debug:
	$(MAKE) -f raylib.mk debug

raylib-release:
	$(MAKE) -f raylib.mk release

esp-debug:
	$(MAKE) -f esp.mk debug

esp-debug:
	$(MAKE) -f esp.mk release

