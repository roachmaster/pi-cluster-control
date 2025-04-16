import sys
import yaml
import json
import re
import os

def to_snake_case(name):
    snake = re.sub(r'[^a-z0-9]+', '_', name.lower()).strip('_')
    if snake and snake[0].isdigit():
        snake = f"scn_{snake}"  # prepend a safe prefix like 'scn_'
    print(f"🔧 Converted to snake_case: '{name}' -> '{snake}'")
    return snake

def prefix_from_key(key):
    return key.upper()


def generate_method_name(prefix, text):
    name = re.sub(r'[^a-z0-9]+', '_', text.lower()).strip('_')
    method = f"{prefix.lower()}_{name}"
    print(f"🔨 Generated method name: '{text}' -> '{method}'")
    return method


def generate_step_entries(steps):
    """Converts BDD step dictionaries into a list of step metadata dicts."""
    entries = []
    for step in steps:
        for key, text in step.items():
            prefix = prefix_from_key(key)
            method_name = generate_method_name(prefix, text)
            full_text = f"{key.capitalize()} {text}"
            step_entry = {
                "method_name": method_name,
                "step_text": full_text,
                "escaped_step_text": json.dumps(full_text)[1:-1],  # Safe C++ string
                "prefix": prefix
            }
            print(f"📝 Step added: {step_entry}")
            entries.append(step_entry)
    return entries


def convert_scenario(feature_file_base, scenario_name, steps):
    print(f"\n🚀 Converting scenario: '{scenario_name}'")
    feature_snake = to_snake_case(feature_file_base)
    scenario_snake = to_snake_case(scenario_name)
    class_data = {
        "interface_class_name": f"{feature_snake}_{scenario_snake}",
        "stub_class_name": f"stub_{feature_snake}_{scenario_snake}",
        "test_class_name": f"{feature_snake}_{scenario_snake}_test",
        "steps": generate_step_entries(steps)
    }
    return scenario_snake, class_data


def main():
    if len(sys.argv) < 2:
        print("Usage: python convert_bdd_yaml_to_step_json.py <path/to/yaml>")
        sys.exit(1)

    yaml_path = sys.argv[1]
    print(f"📥 Loading YAML: {yaml_path}")
    base_path = os.path.splitext(yaml_path)[0]
    feature_file_base = os.path.basename(base_path)

    with open(yaml_path, 'r', encoding='utf-8') as f:
        data = yaml.safe_load(f)

    print(f"📊 Found {len(data[0]['scenarios'])} scenario(s)")

    for scenario in data[0]["scenarios"]:
        snake_name, class_data = convert_scenario(feature_file_base, scenario["name"], scenario["steps"])
        json_path = f"{base_path}_{snake_name}.json"
        with open(json_path, "w", encoding="utf-8") as out:
            json.dump(class_data, out, indent=2)
        print(f"✅ JSON written to: {json_path}")


if __name__ == "__main__":
    main()
