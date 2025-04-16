import re


class ValuesTemplateExpansion:
    _formats: dict[str, dict] = {
        "snake_case": {
            "DETECT_TYPE": r"^[a-z]+(_[a-z0-9]+)*$",
            "TO_SNAKECASE": lambda s: s,
            "FROM_SNAKE_CASE": lambda s: s,
        },
        "camelCase": {
            "DETECT_TYPE": r"^[a-z]+(?:[A-Z][a-z0-9]*)*$",
            "TO_SNAKECASE": lambda s: re.sub(r'(?<!^)(?=[A-Z])', '_', s).lower(),
            "FROM_SNAKE_CASE": lambda s: s.split('_')[0] + ''.join(w.capitalize() for w in s.split('_')[1:])
        },
        "PascalCase": {
            "DETECT_TYPE": r"^[A-Z][a-z0-9]*(?:[A-Z][a-z0-9]*)*$",
            "TO_SNAKECASE": lambda s: re.sub(r'(?<!^)(?=[A-Z])', '_', s).lower(),
            "FROM_SNAKE_CASE": lambda s: ''.join(w.capitalize() for w in s.split('_'))
        },
        "SCREAMING_SNAKE_CASE": {
            "DETECT_TYPE": r"^[A-Z]+(_[A-Z0-9]+)*$",
            "TO_SNAKECASE": lambda s: s.lower(),
            "FROM_SNAKE_CASE": lambda s: s.upper()
        },
        "kebab-case": {
            "DETECT_TYPE": r"^[a-z]+(-[a-z0-9]+)*$",
            "TO_SNAKECASE": lambda s: s.replace('-', '_'),
            "FROM_SNAKE_CASE": lambda s: s.replace('_', '-')
        }
    }

    def getStrValueFormat(self, raw: str) -> str:
        return self.detect_str_format(raw)

    def detect_str_format(self, raw: str) -> str:
        for format_name, rules in self._formats.items():
            pattern = rules.get("DETECT_TYPE")
            if pattern and re.fullmatch(pattern, raw):
                return format_name
        return "unknown"

    def sanitize_value(self, raw: str) -> str:
        return re.sub(r"[^a-zA-Z0-9_-]", "", raw.strip())

    def transform_to_snake_case(self, raw: str, initial_format: str) -> str:
        if initial_format in self._formats:
            transform_fn = self._formats[initial_format].get("TO_SNAKECASE")
            if transform_fn:
                return transform_fn(raw)
        return raw

    def createSCREAMING_SNAKE_CASE(self, snake_value: str) -> str:
        return self._formats["SCREAMING_SNAKE_CASE"]["FROM_SNAKE_CASE"](snake_value)

    def createPascalCase(self, snake_value: str) -> str:
        return self._formats["PascalCase"]["FROM_SNAKE_CASE"](snake_value)

    def createcamelCase(self, snake_value: str) -> str:
        return self._formats["camelCase"]["FROM_SNAKE_CASE"](snake_value)

    def createkebab_case(self, snake_value: str) -> str:
        return self._formats["kebab-case"]["FROM_SNAKE_CASE"](snake_value)

    def expands_to_dict(self, value_name: str, value: str) -> dict[str, str]:
        sanitized_key = self.sanitize_value(value_name)
        sanitized_val = self.sanitize_value(value)

        inferred_key_format = self.detect_str_format(sanitized_key)
        inferred_val_format = self.detect_str_format(sanitized_val)

        key_snake = self.transform_to_snake_case(sanitized_key, inferred_key_format)
        val_snake = self.transform_to_snake_case(sanitized_val, inferred_val_format)

        return {
            f"{key_snake}_snake_case": val_snake,
            f"{key_snake}_SCREAMING_SNAKE_CASE": self.createSCREAMING_SNAKE_CASE(val_snake),
            f"{key_snake}_PascalCase": self.createPascalCase(val_snake),
            f"{key_snake}_camelCase": self.createcamelCase(val_snake),
            f"{key_snake}_kebab_case": self.createkebab_case(val_snake),
        }