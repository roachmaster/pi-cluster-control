import sys
import yaml
import json
import re
import os

def to_snake_case(name):
    snake = re.sub(r'[^a-z0-9]+', '_', name.lower()).strip('_')
    print(f"🔧 Converted to snake_case: '{name}' -> '{snake}'")
    return snake

def prefix_from_key(key):
    return key.upper()

def generate_method_name(prefix, text):
    name = re.sub(r'[^a-z0-9]+', '_', text.lower()).strip('_')
    method = f"{prefix.lower()}_{name}"
    print(f"🔨 Generated method name: '{text}' -> '{method}'")
    return method

def convert_scenario(name, steps):
    print(f"\n🚀 Converting scenario: '{name}'")
    snake_name = to_snake_case(name)
    class_data = {
        "interface_class_name": f"cppforge_{snake_name}_steps",
        "stub_class_name": f"stub_{snake_name}_steps",
        "test_class_name": f"cppforge_{snake_name}_test",
        "steps": []
    }

    for step in steps:
        for key, text in step.items():
            prefix = prefix_from_key(key)
            method_name = generate_method_name(prefix, text)
            step_entry = {
                "method_name": method_name,
                "step_text": f"{key.capitalize()} {text}",
                "prefix": prefix
            }
            print(f"📝 Step added: {step_entry}")
            class_data["steps"].append(step_entry)

    return snake_name, class_data

def main():
    if len(sys.argv) < 2:
        print("Usage: python convert_bdd_yaml_to_step_json.py <path/to/yaml>")
        sys.exit(1)

    yaml_path = sys.argv[1]
    print(f"📥 Loading YAML: {yaml_path}")
    base_path = os.path.splitext(yaml_path)[0]

    with open(yaml_path, 'r', encoding='utf-8') as f:
        data = yaml.safe_load(f)

    print(f"📊 Found {len(data[0]['scenarios'])} scenario(s)")

    for scenario in data[0]["scenarios"]:
        snake_name, class_data = convert_scenario(scenario["name"], scenario["steps"])
        json_path = f"{base_path}__{snake_name}.json"
        with open(json_path, "w", encoding="utf-8") as out:
            json.dump(class_data, out, indent=2)
        print(f"✅ JSON written to: {json_path}")

if __name__ == "__main__":
    main()
