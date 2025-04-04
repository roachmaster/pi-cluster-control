import sys, yaml, os
from antlr4 import InputStream, CommonTokenStream
from parser.BDDLexer import BDDLexer
from parser.BDDParser import BDDParser
from parser.BDDVisitor import BDDVisitor

def clean_input(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()
    return "\n".join(line.strip() for line in lines if line.strip()) + "\n"

class BDDToYaml(BDDVisitor):
    def visitDocument(self, ctx):
        return [self.visit(f) for f in ctx.feature()]

    def visitFeature(self, ctx):
        feature_line = ctx.FEATURE_HEADER().getText().replace('Feature:', '').strip()
        return {
            "feature": feature_line,
            "scenarios": [self.visit(s) for s in ctx.scenario()]
        }

    def visitScenario(self, ctx):
        scenario_line = ctx.SCENARIO_HEADER().getText().replace('Scenario:', '').strip()
        return {
            "name": scenario_line,
            "steps": [self.visit(s) for s in ctx.step()]
        }

    def visitStep(self, ctx):
        full_text = ctx.STEP_START().getText()
        keyword, rest = full_text.split(maxsplit=1)
        return {keyword.lower(): rest.strip()}

if __name__ == "__main__":
    input_path = sys.argv[1]
    yaml_path = os.path.splitext(input_path)[0] + ".yaml"

    cleaned_input = clean_input(input_path)
    stream = InputStream(cleaned_input)
    lexer = BDDLexer(stream)
    tokens = CommonTokenStream(lexer)
    parser = BDDParser(tokens)
    tree = parser.document()
    result = BDDToYaml().visit(tree)

    with open(yaml_path, "w", encoding="utf-8") as out:
        yaml.dump(result, out, sort_keys=False)

    print(f"✅ YAML written to: {yaml_path}")
