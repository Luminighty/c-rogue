PYTHON=/usr/bin/python3

.PHONY: debug release


export_assets:
	$(PYTHON) ./scripts/png_to_header.py > ./platform_esp/main/font.c


debug:
	command -v idf.py >/dev/null || { echo "idf.py not found"; exit 1; }
	cd ./platform_esp && idf.py -p /dev/ttyUSB0 flash monitor


release:
	command -v idf.py >/dev/null || { echo "idf.py not found"; exit 1; }
	cd ./platform_esp && idf.py -p /dev/ttyUSB0 flash

