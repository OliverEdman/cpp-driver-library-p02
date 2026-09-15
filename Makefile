format:
	@clang-format -i $$(find . -name '*.h') $$(find . -name '*.c')

check-format:
	@clang-format --dry-run --Werror $$(find . -name '*.h') $$(find . -name '*.c')
