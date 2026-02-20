/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Unit tests for core types (Personne A)
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <sstream>

#include "nts/AComponent.hpp"
#include "nts/Circuit.hpp"
#include "nts/Errors.hpp"
#include "nts/Factory.hpp"
#include "nts/IComponent.hpp"
#include "nts/Lexer.hpp"
#include "nts/Parser.hpp"
#include "nts/Shell.hpp"
#include "nts/Tristate.hpp"
#include "nts/TristateLogic.hpp"
#include "nts/components/AndGate.hpp"
#include "nts/components/Clock.hpp"
#include "nts/components/False.hpp"
#include "nts/components/Input.hpp"
#include "nts/components/NotGate.hpp"
#include "nts/components/OrGate.hpp"
#include "nts/components/Output.hpp"
#include "nts/components/True.hpp"
#include "nts/components/XorGate.hpp"

using namespace nts;

Test(tristate, underlying_values) {
  cr_assert_eq(static_cast<int>(Undefined), -1, "Undefined should be -1");
  cr_assert_eq(static_cast<int>(False), 0, "False should be 0");
  cr_assert_eq(static_cast<int>(True), 1, "True should be 1");
}

Test(tristate, enum_completeness) {
  Tristate values[] = {Undefined, False, True};
  int count = 0;
  for (auto v : values) {
    switch (v) {
    case Undefined:
      count++;
      break;
    case False:
      count++;
      break;
    case True:
      count++;
      break;
    }
  }
  cr_assert_eq(count, 3, "All three tristate values should be covered");
}

Test(tristate_logic, and_gate_basic) {
  cr_assert_eq(TristateLogic::andGate(True, True), True);
  cr_assert_eq(TristateLogic::andGate(False, True), False);
  cr_assert_eq(TristateLogic::andGate(True, False), False);
  cr_assert_eq(TristateLogic::andGate(False, False), False);
}

Test(tristate_logic, and_gate_with_undefined) {
  cr_assert_eq(TristateLogic::andGate(Undefined, False), False);
  cr_assert_eq(TristateLogic::andGate(False, Undefined), False);
  cr_assert_eq(TristateLogic::andGate(True, Undefined), Undefined);
  cr_assert_eq(TristateLogic::andGate(Undefined, True), Undefined);
  cr_assert_eq(TristateLogic::andGate(Undefined, Undefined), Undefined);
}

Test(tristate_logic, or_gate_basic) {
  cr_assert_eq(TristateLogic::orGate(True, True), True);
  cr_assert_eq(TristateLogic::orGate(False, True), True);
  cr_assert_eq(TristateLogic::orGate(True, False), True);
  cr_assert_eq(TristateLogic::orGate(False, False), False);
}

Test(tristate_logic, or_gate_with_undefined) {
  cr_assert_eq(TristateLogic::orGate(True, Undefined), True);
  cr_assert_eq(TristateLogic::orGate(Undefined, True), True);
  cr_assert_eq(TristateLogic::orGate(False, Undefined), Undefined);
  cr_assert_eq(TristateLogic::orGate(Undefined, False), Undefined);
  cr_assert_eq(TristateLogic::orGate(Undefined, Undefined), Undefined);
}

Test(tristate_logic, xor_gate_basic) {
  cr_assert_eq(TristateLogic::xorGate(True, True), False);
  cr_assert_eq(TristateLogic::xorGate(False, True), True);
  cr_assert_eq(TristateLogic::xorGate(True, False), True);
  cr_assert_eq(TristateLogic::xorGate(False, False), False);
}

Test(tristate_logic, xor_gate_with_undefined) {
  cr_assert_eq(TristateLogic::xorGate(True, Undefined), Undefined);
  cr_assert_eq(TristateLogic::xorGate(Undefined, True), Undefined);
  cr_assert_eq(TristateLogic::xorGate(False, Undefined), Undefined);
  cr_assert_eq(TristateLogic::xorGate(Undefined, False), Undefined);
  cr_assert_eq(TristateLogic::xorGate(Undefined, Undefined), Undefined);
}

Test(tristate_logic, not_gate) {
  cr_assert_eq(TristateLogic::notGate(True), False);
  cr_assert_eq(TristateLogic::notGate(False), True);
  cr_assert_eq(TristateLogic::notGate(Undefined), Undefined);
}

Test(tristate_logic, nand_gate_basic) {
  cr_assert_eq(TristateLogic::nandGate(True, True), False);
  cr_assert_eq(TristateLogic::nandGate(False, True), True);
  cr_assert_eq(TristateLogic::nandGate(True, False), True);
  cr_assert_eq(TristateLogic::nandGate(False, False), True);
}

Test(tristate_logic, nand_gate_with_undefined) {
  cr_assert_eq(TristateLogic::nandGate(False, Undefined), True);
  cr_assert_eq(TristateLogic::nandGate(Undefined, False), True);
  cr_assert_eq(TristateLogic::nandGate(True, Undefined), Undefined);
  cr_assert_eq(TristateLogic::nandGate(Undefined, True), Undefined);
}

Test(tristate_logic, nor_gate_basic) {
  cr_assert_eq(TristateLogic::norGate(True, True), False);
  cr_assert_eq(TristateLogic::norGate(False, True), False);
  cr_assert_eq(TristateLogic::norGate(True, False), False);
  cr_assert_eq(TristateLogic::norGate(False, False), True);
}

Test(tristate_logic, nor_gate_with_undefined) {
  cr_assert_eq(TristateLogic::norGate(True, Undefined), False);
  cr_assert_eq(TristateLogic::norGate(Undefined, True), False);
  cr_assert_eq(TristateLogic::norGate(False, Undefined), Undefined);
  cr_assert_eq(TristateLogic::norGate(Undefined, False), Undefined);
}

Test(tristate_logic, xnor_gate_basic) {
  cr_assert_eq(TristateLogic::xnorGate(True, True), True);
  cr_assert_eq(TristateLogic::xnorGate(False, True), False);
  cr_assert_eq(TristateLogic::xnorGate(True, False), False);
  cr_assert_eq(TristateLogic::xnorGate(False, False), True);
}

Test(tristate_logic, xnor_gate_with_undefined) {
  cr_assert_eq(TristateLogic::xnorGate(True, Undefined), Undefined);
  cr_assert_eq(TristateLogic::xnorGate(Undefined, True), Undefined);
  cr_assert_eq(TristateLogic::xnorGate(False, Undefined), Undefined);
  cr_assert_eq(TristateLogic::xnorGate(Undefined, False), Undefined);
}

namespace {

struct DummyComponent : IComponent {
  Tristate value = Undefined;

  void simulate(std::size_t) override {}

  Tristate compute(std::size_t) override { return value; }

  void setLink(std::size_t, IComponent &, std::size_t) override {}
};

struct TestableComponent : AComponent {
  Tristate value = Undefined;

  void simulate(std::size_t) override {}

  Tristate compute(std::size_t pin) override {
    if (pin == 1)
      return value;
    return Undefined;
  }

  Tristate readLinked(std::size_t pin) { return getLinkValue(pin); }
};

struct TestFactory : IComponentFactory {
  std::unique_ptr<IComponent>
  createComponent(const std::string &, const std::string &) const override {
    return std::make_unique<TestableComponent>();
  }
};

}

Test(icomponent, can_derive_and_use_interface) {
  DummyComponent comp;
  comp.value = True;

  cr_assert_eq(comp.compute(0), True,
               "Derived IComponent should return the value set in compute()");
}

Test(icomponent, polymorphism_through_pointer) {
  std::unique_ptr<IComponent> comp = std::make_unique<DummyComponent>();
  dynamic_cast<DummyComponent *>(comp.get())->value = False;
  cr_assert_eq(comp->compute(0), False);
}

Test(acomponent, name_accessors) {
  TestableComponent comp;

  comp.setName("my_component");
  cr_assert_str_eq(comp.getName().c_str(), "my_component");
}

Test(acomponent, bidirectional_link_and_get_link_value) {
  TestableComponent a;
  TestableComponent b;

  a.value = True;
  b.value = False;

  a.setLink(1, b, 1);

  cr_assert_eq(
      b.readLinked(1), True,
      "Reading pin 1 on b through link should return a's value (True)");

  cr_assert_eq(
      a.readLinked(1), False,
      "Reading pin 1 on a through link should return b's value (False)");
}

Test(acomponent, compute_no_infinite_recursion) {
  TestableComponent a;
  TestableComponent b;

  a.setLink(1, b, 1);
  b.setLink(1, a, 1);

  Tristate result = a.readLinked(1);
  cr_assert_eq(result, Undefined,
               "Circular link should return Undefined (recursion guard)");
}

Test(acomponent, unlinked_pin_returns_undefined) {
  TestableComponent comp;
  cr_assert_eq(comp.readLinked(42), Undefined,
               "Unlinked pin should return Undefined");
}

Test(acomponent, set_and_get_pin) {
  TestableComponent comp;
  comp.setPin(1, True);
  cr_assert_eq(comp.getPin(1), True);
  comp.setPin(1, False);
  cr_assert_eq(comp.getPin(1), False);
  cr_assert_eq(comp.getPin(99), Undefined, "Unset pin returns Undefined");
}

Test(circuit, add_and_has_component) {
  Circuit c;
  c.addComponent("foo", std::make_unique<TestableComponent>());
  cr_assert(c.hasComponent("foo"));
  cr_assert_not(c.hasComponent("bar"));
}

Test(circuit, duplicate_name_throws) {
  Circuit c;
  c.addComponent("foo", std::make_unique<TestableComponent>());
  bool thrown = false;
  try {
    c.addComponent("foo", std::make_unique<TestableComponent>());
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Adding duplicate component should throw");
}

Test(circuit, get_unknown_throws) {
  Circuit c;
  bool thrown = false;
  try {
    (void)c.getComponent("nonexistent");
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Getting unknown component should throw");
}

Test(circuit, simulate_increments_tick) {
  Circuit c;
  c.addComponent("a", std::make_unique<TestableComponent>());
  cr_assert_eq(c.tick(), 0);
  c.simulate();
  cr_assert_eq(c.tick(), 1);
  c.simulate();
  cr_assert_eq(c.tick(), 2);
}

Test(circuit, set_input_value) {
  Circuit c;
  auto comp = std::make_unique<TestableComponent>();
  auto *ptr = comp.get();
  c.addComponent("in1", std::move(comp));
  c.addInputName("in1");

  c.setInputValue("in1", "1");
  cr_assert_eq(ptr->getPin(1), True);

  c.setInputValue("in1", "0");
  cr_assert_eq(ptr->getPin(1), False);

  c.setInputValue("in1", "U");
  cr_assert_eq(ptr->getPin(1), Undefined);
}

Test(circuit, set_input_unknown_name_throws) {
  Circuit c;
  c.addComponent("in1", std::make_unique<TestableComponent>());
  c.addInputName("in1");
  bool thrown = false;
  try {
    c.setInputValue("nonexistent", "1");
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown);
}

Test(circuit, set_input_invalid_value_throws) {
  Circuit c;
  c.addComponent("in1", std::make_unique<TestableComponent>());
  c.addInputName("in1");
  bool thrown = false;
  try {
    c.setInputValue("in1", "X");
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown);
}

Test(circuit, display_format, .init = cr_redirect_stdout) {
  Circuit c;
  auto in = std::make_unique<TestableComponent>();
  in->value = True;
  auto out = std::make_unique<TestableComponent>();
  out->value = False;

  c.addComponent("in_a", std::move(in));
  c.addComponent("out_b", std::move(out));
  c.addInputName("in_a");
  c.addOutputName("out_b");

  c.display();

  cr_assert_stdout_eq_str("tick: 0\n"
                          "input(s):\n"
                          "  in_a: 1\n"
                          "output(s):\n"
                          "  out_b: 0\n");
}

Test(parser, parse_minimal_valid_file) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss(".chipsets:\n"
                         "input a\n"
                         "output b\n"
                         ".links:\n"
                         "a:1 b:1\n");

  Circuit circuit = parser.parse(iss);

  cr_assert(circuit.hasComponent("a"));
  cr_assert(circuit.hasComponent("b"));

  auto &a = dynamic_cast<TestableComponent &>(circuit.getComponent("a"));
  auto &b = dynamic_cast<TestableComponent &>(circuit.getComponent("b"));

  a.value = True;
  b.value = False;

  cr_assert_eq(b.readLinked(1), True,
               "Link from b to a should read True (a's value)");
  cr_assert_eq(a.readLinked(1), False,
               "Link from a to b should read False (b's value)");
}

Test(parser, duplicate_component_name_throws) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss(".chipsets:\n"
                         "input a\n"
                         "input a\n");

  bool thrown = false;
  try {
    (void)parser.parse(iss);
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Expected ParseError on duplicate component name");
}

Test(parser, links_to_unknown_component_throw) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss(".chipsets:\n"
                         "input a\n"
                         ".links:\n"
                         "a:1 b:1\n");

  bool thrown = false;
  try {
    (void)parser.parse(iss);
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown,
            "Expected ParseError when link references unknown component");
}

Test(parser, no_chipsets_throws) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss("# Empty .chipsets section\n"
                         ".chipsets:\n"
                         ".links:\n");

  bool thrown = false;
  try {
    (void)parser.parse(iss);
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Expected ParseError when no chipsets are defined");
}

Test(parser, comments_are_stripped) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss("# This is a comment\n"
                         ".chipsets:\n"
                         "input a  # inline comment\n"
                         "output b\n"
                         ".links:\n"
                         "a:1 b:1 # link comment\n");

  Circuit circuit = parser.parse(iss);
  cr_assert(circuit.hasComponent("a"));
  cr_assert(circuit.hasComponent("b"));
}

Test(parser, registers_input_output_names) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss(".chipsets:\n"
                         "input in1\n"
                         "input in2\n"
                         "output out1\n"
                         ".links:\n"
                         "in1:1 out1:1\n");

  Circuit circuit = parser.parse(iss);
  cr_assert_eq(circuit.inputNames().size(), 2u);
  cr_assert_eq(circuit.outputNames().size(), 1u);
}

Test(parser, file_not_found_throws) {
  TestFactory factory;
  Parser parser(factory);

  bool thrown = false;
  try {
    (void)parser.parse("/nonexistent/path.nts");
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Expected ParseError when file not found");
}

Test(parser, invalid_chipset_line_throws) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss(".chipsets:\n"
                         "input\n");

  bool thrown = false;
  try {
    (void)parser.parse(iss);
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Expected ParseError on invalid chipset line");
}

Test(parser, invalid_link_endpoint_throws) {
  TestFactory factory;
  Parser parser(factory);

  std::istringstream iss(".chipsets:\n"
                         "input a\n"
                         "output b\n"
                         ".links:\n"
                         "a b:1\n");

  bool thrown = false;
  try {
    (void)parser.parse(iss);
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "Expected ParseError on invalid link endpoint (no colon)");
}

Test(errors, nts_exception_inherits_std_exception) {
  bool caught_as_exception = false;
  try {
    throw NtsException("test error");
  } catch (const std::exception &e) {
    caught_as_exception = true;
    cr_assert_str_eq(e.what(), "test error");
  }
  cr_assert(caught_as_exception);
}

Test(errors, parse_error_inherits_nts_exception) {
  bool caught_as_nts = false;
  try {
    throw ParseError("parse error");
  } catch (const NtsException &e) {
    caught_as_nts = true;
    cr_assert_str_eq(e.what(), "parse error");
  }
  cr_assert(caught_as_nts);
}

Test(lexer, token_parsing) {
  Lexer lexer(".chipsets:\ninput a\n.links:\na:1 b:1\n");

  Token t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::CHIPSETS_SECTION);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::COLON);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::NEWLINE);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::IDENTIFIER);
  cr_assert_str_eq(t.value.c_str(), "input");

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::IDENTIFIER);
  cr_assert_str_eq(t.value.c_str(), "a");

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::NEWLINE);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::LINKS_SECTION);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::COLON);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::NEWLINE);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::IDENTIFIER);
  cr_assert_str_eq(t.value.c_str(), "a");

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::COLON);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::NUMBER);
  cr_assert_str_eq(t.value.c_str(), "1");

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::IDENTIFIER);
  cr_assert_str_eq(t.value.c_str(), "b");

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::COLON);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::NUMBER);
  cr_assert_str_eq(t.value.c_str(), "1");

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::NEWLINE);

  t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::EOF_TOKEN);
}

Test(lexer, unknown_token) {
  Lexer lexer("~");
  Token t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::UNKNOWN);
  cr_assert_str_eq(t.value.c_str(), "~");
}

Test(shell, basic_run_and_exit, .init = cr_redirect_stdout) {
  Circuit c;
  Shell shell(c);

  std::istringstream mock_input("exit\n");
  std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());

  shell.run();

  std::cin.rdbuf(old_cin);
  cr_assert(true, "Shell should be able to exit cleanly");
}

Test(shell, unknown_command_prints_error, .init = cr_redirect_stderr) {
  Circuit c;
  Shell shell(c);

  std::istringstream mock_input("unknown\nexit\n");
  std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());

  shell.run();

  std::cin.rdbuf(old_cin);

  cr_assert_stderr_eq_str("Error: Unknown command: 'unknown'\n");
}

Test(shell, valid_commands_no_crash, .init = cr_redirect_stdout) {
  Circuit c;
  Shell shell(c);

  std::istringstream mock_input("simulate\ndisplay\nexit\n");
  std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());

  shell.run();

  std::cin.rdbuf(old_cin);
  cr_assert(true,
            "Shell should run simulate and display without thrown exceptions");
}

Test(shell, set_input_command_parsing, .init = cr_redirect_stdout) {
  Circuit c;
  auto in = std::make_unique<TestableComponent>();
  auto *ptr = in.get();
  c.addComponent("my_in", std::move(in));
  c.addInputName("my_in");

  Shell shell(c);
  std::istringstream mock_input("my_in=1\nexit\n");
  std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());

  shell.run();

  std::cin.rdbuf(old_cin);

  cr_assert_eq(ptr->getPin(1), True,
               "Shell should set the input value correctly");
}

Test(input, initial_value_is_undefined) {
  Input inp("inp");
  cr_assert_eq(inp.compute(1), Undefined,
               "Input should start with Undefined at pin 1");
}

Test(input, set_value_not_applied_before_simulate) {
  Input inp("inp");
  inp.setValue(True);
  cr_assert_eq(inp.compute(1), Undefined,
               "setValue() should not immediately update pin 1");
}

Test(input, simulate_applies_true) {
  Input inp("inp");
  inp.setValue(True);
  inp.simulate(1);
  cr_assert_eq(inp.compute(1), True,
               "simulate() should apply True to pin 1");
}

Test(input, simulate_applies_false) {
  Input inp("inp");
  inp.setValue(False);
  inp.simulate(1);
  cr_assert_eq(inp.compute(1), False,
               "simulate() should apply False to pin 1");
}

Test(input, simulate_applies_undefined) {
  Input inp("inp");
  inp.setValue(True);
  inp.simulate(1);
  inp.setValue(Undefined);
  inp.simulate(2);
  cr_assert_eq(inp.compute(1), Undefined,
               "simulate() should apply Undefined if set via setValue()");
}

Test(input, compute_invalid_pin_throws) {
  Input inp("inp");
  bool thrown = false;
  try {
    inp.compute(2);
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown, "compute() with pin != 1 should throw NtsException");
}

Test(output, compute_unlinked_returns_undefined) {
  Output out("out");
  cr_assert_eq(out.compute(1), Undefined,
               "Unlinked Output should return Undefined");
}

Test(output, compute_reads_linked_component) {
  Output out("out");
  TestableComponent source;
  source.value = True;
  out.setLink(1, source, 1);
  cr_assert_eq(out.compute(1), True,
               "Output should return the linked component's value");
}

Test(output, compute_invalid_pin_throws) {
  Output out("out");
  bool thrown = false;
  try {
    out.compute(2);
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown, "compute() with pin != 1 should throw NtsException");
}

Test(true_comp, compute_always_returns_true) {
  TrueComp tc("vcc");
  cr_assert_eq(tc.compute(1), True,
               "TrueComp should always return True at pin 1");
}

Test(true_comp, simulate_does_not_change_value) {
  TrueComp tc("vcc");
  tc.simulate(1);
  cr_assert_eq(tc.compute(1), True,
               "simulate() should not affect TrueComp's output");
}

Test(true_comp, compute_invalid_pin_throws) {
  TrueComp tc("vcc");
  bool thrown = false;
  try {
    tc.compute(2);
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown, "compute() with pin != 1 should throw NtsException");
}

Test(false_comp, compute_always_returns_false) {
  FalseComp fc("gnd");
  cr_assert_eq(fc.compute(1), False,
               "FalseComp should always return False at pin 1");
}

Test(false_comp, simulate_does_not_change_value) {
  FalseComp fc("gnd");
  fc.simulate(1);
  cr_assert_eq(fc.compute(1), False,
               "simulate() should not affect FalseComp's output");
}

Test(false_comp, compute_invalid_pin_throws) {
  FalseComp fc("gnd");
  bool thrown = false;
  try {
    fc.compute(2);
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown, "compute() with pin != 1 should throw NtsException");
}

Test(clock, initial_value_is_undefined) {
  Clock clk("cl");
  cr_assert_eq(clk.compute(1), Undefined,
               "Clock should start with Undefined before any simulate");
}

Test(clock, undefined_stays_undefined_after_simulate) {
  Clock clk("cl");
  clk.simulate(1);
  cr_assert_eq(clk.compute(1), Undefined,
               "Undefined clock should remain Undefined after simulate");
  clk.simulate(2);
  cr_assert_eq(clk.compute(1), Undefined,
               "Undefined clock should remain Undefined after multiple simulates");
}

Test(clock, toggles_from_false) {
  Clock clk("cl");
  clk.setValue(False);
  clk.simulate(1);
  cr_assert_eq(clk.compute(1), False, "Tick 1: clock should be False");
  clk.simulate(2);
  cr_assert_eq(clk.compute(1), True,  "Tick 2: clock should toggle to True");
  clk.simulate(3);
  cr_assert_eq(clk.compute(1), False, "Tick 3: clock should toggle back to False");
}

Test(clock, toggles_from_true) {
  Clock clk("cl");
  clk.setValue(True);
  clk.simulate(1);
  cr_assert_eq(clk.compute(1), True,  "Tick 1: clock should be True");
  clk.simulate(2);
  cr_assert_eq(clk.compute(1), False, "Tick 2: clock should toggle to False");
}

Test(clock, set_value_overrides_toggle) {
  Clock clk("cl");
  clk.setValue(False);
  clk.simulate(1);
  clk.setValue(False);
  clk.simulate(2);
  cr_assert_eq(clk.compute(1), False,
               "setValue() should override the automatic toggle");
}

Test(and_gate, unlinked_pins_return_undefined) {
  AndGate g("g");
  cr_assert_eq(g.compute(1), Undefined, "Unlinked pin 1 should be Undefined");
  cr_assert_eq(g.compute(2), Undefined, "Unlinked pin 2 should be Undefined");
  cr_assert_eq(g.compute(3), Undefined, "Output with both inputs Undefined should be Undefined");
}

Test(and_gate, invalid_pin_throws) {
  AndGate g("g");
  bool thrown = false;
  try { g.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(0) should throw");
  thrown = false;
  try { g.compute(4); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(4) should throw");
}

Test(and_gate, output_true_and_true) {
  AndGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = True;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "True AND True = True");
}

Test(and_gate, output_false_and_true) {
  AndGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = True;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "False AND True = False");
}

Test(and_gate, output_false_and_false) {
  AndGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "False AND False = False");
}

Test(and_gate, output_undefined_absorbs_false) {
  AndGate g("g");
  TestableComponent a, b;
  a.value = Undefined; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "Undefined AND False = False (absorbing)");
}

Test(and_gate, output_undefined_and_true_is_undefined) {
  AndGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), Undefined, "True AND Undefined = Undefined");
}

Test(and_gate, input_pin_returns_linked_value) {
  AndGate g("g");
  TestableComponent src;
  src.value = True;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(1), True, "compute(1) should return the linked value");
}

Test(and_gate, simulate_updates_tick) {
  AndGate g("g");
  g.simulate(42);
  cr_assert_str_eq(g.getName().c_str(), "g", "Name should still be accessible after simulate");
}

Test(or_gate, unlinked_output_returns_undefined) {
  OrGate g("g");
  cr_assert_eq(g.compute(3), Undefined, "Unlinked OrGate output should be Undefined");
}

Test(or_gate, invalid_pin_throws) {
  OrGate g("g");
  bool thrown = false;
  try { g.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(0) should throw");
  thrown = false;
  try { g.compute(4); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(4) should throw");
}

Test(or_gate, output_true_or_false) {
  OrGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "True OR False = True");
}

Test(or_gate, output_false_or_false) {
  OrGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "False OR False = False");
}

Test(or_gate, output_true_absorbs_undefined) {
  OrGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "True OR Undefined = True (absorbing)");
}

Test(or_gate, output_false_or_undefined_is_undefined) {
  OrGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), Undefined, "False OR Undefined = Undefined");
}

Test(xor_gate, unlinked_output_returns_undefined) {
  XorGate g("g");
  cr_assert_eq(g.compute(3), Undefined, "Unlinked XorGate output should be Undefined");
}

Test(xor_gate, invalid_pin_throws) {
  XorGate g("g");
  bool thrown = false;
  try { g.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(0) should throw");
  thrown = false;
  try { g.compute(4); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(4) should throw");
}

Test(xor_gate, output_true_xor_true) {
  XorGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = True;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "True XOR True = False");
}

Test(xor_gate, output_true_xor_false) {
  XorGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "True XOR False = True");
}

Test(xor_gate, output_false_xor_false) {
  XorGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "False XOR False = False");
}

Test(xor_gate, undefined_input_yields_undefined) {
  XorGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), Undefined, "True XOR Undefined = Undefined");
}

Test(not_gate, unlinked_pins_return_undefined) {
  NotGate g("g");
  cr_assert_eq(g.compute(1), Undefined, "Unlinked pin 1 should be Undefined");
  cr_assert_eq(g.compute(2), Undefined, "Unlinked pin 2 (output) should be Undefined");
}

Test(not_gate, invalid_pin_throws) {
  NotGate g("g");
  bool thrown = false;
  try { g.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(0) should throw");
  thrown = false;
  try { g.compute(3); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(3) should throw");
}

Test(not_gate, output_not_true) {
  NotGate g("g");
  TestableComponent src;
  src.value = True;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(2), False, "NOT True = False");
}

Test(not_gate, output_not_false) {
  NotGate g("g");
  TestableComponent src;
  src.value = False;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(2), True, "NOT False = True");
}

Test(not_gate, output_not_undefined) {
  NotGate g("g");
  TestableComponent src;
  src.value = Undefined;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(2), Undefined, "NOT Undefined = Undefined");
}

Test(not_gate, input_pin_returns_linked_value) {
  NotGate g("g");
  TestableComponent src;
  src.value = False;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(1), False, "compute(1) should return the linked input value");
}
