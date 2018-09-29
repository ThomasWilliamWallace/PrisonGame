.PHONY: clean All

All:
	@echo "----------Building project:[ GamePersonalities - Debug ]----------"
	@cd "GamePersonalities" && "$(MAKE)" -f  "GamePersonalities.mk"
clean:
	@echo "----------Cleaning project:[ GamePersonalities - Debug ]----------"
	@cd "GamePersonalities" && "$(MAKE)" -f  "GamePersonalities.mk" clean
