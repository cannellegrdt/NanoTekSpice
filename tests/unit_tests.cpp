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
#include "nts/ComponentFactory.hpp"
#include "nts/components/C2716.hpp"
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
#include "nts/components/NandGate.hpp"
#include "nts/components/NorGate.hpp"
#include "nts/components/NotGate.hpp"
#include "nts/components/OrGate.hpp"
#include "nts/components/Output.hpp"
#include "nts/components/True.hpp"
#include "nts/components/XorGate.hpp"
#include "nts/components/C4001.hpp"
#include "nts/components/C4011.hpp"
#include "nts/components/C4030.hpp"
#include "nts/components/C4069.hpp"
#include "nts/components/C4071.hpp"
#include "nts/components/C4081.hpp"
#include "nts/components/C4008.hpp"
#include "nts/components/C4013.hpp"
#include "nts/components/C4017.hpp"
#include "nts/components/C4040.hpp"
#include "nts/components/C4094.hpp"
#include "nts/components/C4512.hpp"
#include "nts/components/C4514.hpp"
#include "nts/components/C4801.hpp"
#include "nts/components/Logger.hpp"
#include <chrono>
#include <csignal>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>


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

Test(nand_gate, unlinked_output_returns_undefined) {
  NandGate g("g");
  cr_assert_eq(g.compute(3), Undefined,
               "Unlinked NandGate output should be Undefined");
}

Test(nand_gate, invalid_pin_throws) {
  NandGate g("g");
  bool thrown = false;
  try { g.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(0) should throw");
  thrown = false;
  try { g.compute(4); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(4) should throw");
}

Test(nand_gate, output_true_nand_true) {
  NandGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = True;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "True NAND True = False");
}

Test(nand_gate, output_false_nand_false) {
  NandGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "False NAND False = True");
}

Test(nand_gate, output_true_nand_false) {
  NandGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "True NAND False = True");
}

Test(nand_gate, false_absorbs_undefined) {
  NandGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "False NAND Undefined = True (absorbing)");
}

Test(nand_gate, true_nand_undefined_is_undefined) {
  NandGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), Undefined, "True NAND Undefined = Undefined");
}

Test(nand_gate, input_pin_returns_linked_value) {
  NandGate g("g");
  TestableComponent src;
  src.value = True;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(1), True, "compute(1) should return the linked value");
}

Test(nor_gate, unlinked_output_returns_undefined) {
  NorGate g("g");
  cr_assert_eq(g.compute(3), Undefined,
               "Unlinked NorGate output should be Undefined");
}

Test(nor_gate, invalid_pin_throws) {
  NorGate g("g");
  bool thrown = false;
  try { g.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(0) should throw");
  thrown = false;
  try { g.compute(4); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "compute(4) should throw");
}

Test(nor_gate, output_false_nor_false) {
  NorGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), True, "False NOR False = True");
}

Test(nor_gate, output_true_nor_false) {
  NorGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = False;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "True NOR False = False");
}

Test(nor_gate, output_true_nor_true) {
  NorGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = True;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "True NOR True = False");
}

Test(nor_gate, true_absorbs_undefined) {
  NorGate g("g");
  TestableComponent a, b;
  a.value = True; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), False, "True NOR Undefined = False (absorbing)");
}

Test(nor_gate, false_nor_undefined_is_undefined) {
  NorGate g("g");
  TestableComponent a, b;
  a.value = False; b.value = Undefined;
  g.setLink(1, a, 1);
  g.setLink(2, b, 1);
  cr_assert_eq(g.compute(3), Undefined, "False NOR Undefined = Undefined");
}

Test(c4001, power_pins_throw) {
  C4001 chip("chip");
  bool t7 = false, t14 = false;
  try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
  try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
  cr_assert(t7,  "Pin 7 (VSS) must throw");
  cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4001, invalid_pin_throws) {
  C4001 chip("chip");
  bool thrown = false;
  try { chip.compute(0); } catch (const NtsException &) { thrown = true; }
  cr_assert(thrown, "Pin 0 must throw");
}

Test(c4001, gate1_false_nor_false) {
  C4001 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), True, "Gate1 (pins 1,2->3): F NOR F = T");
}

Test(c4001, gate1_true_nor_false) {
  C4001 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): T NOR F = F");
}

Test(c4001, gate2_nor) {
  C4001 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(5, a, 1);
  chip.setLink(6, b, 1);
  cr_assert_eq(chip.compute(4), True, "Gate2 (pins 5,6->4): F NOR F = T");
}

Test(c4001, gate3_nor) {
  C4001 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(8, a, 1);
  chip.setLink(9, b, 1);
  cr_assert_eq(chip.compute(10), False, "Gate3 (pins 8,9->10): T NOR T = F");
}

Test(c4001, gate4_nor) {
  C4001 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(12, a, 1);
  chip.setLink(13, b, 1);
  cr_assert_eq(chip.compute(11), True, "Gate4 (pins 12,13->11): F NOR F = T");
}

Test(c4001, simulate_no_crash) {
  C4001 chip("chip");
  chip.simulate(1);
  cr_assert(true, "simulate() should not throw");
}

Test(c4011, power_pins_throw) {
  C4011 chip("chip");
  bool t7 = false, t14 = false;
  try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
  try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
  cr_assert(t7,  "Pin 7 (VSS) must throw");
  cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4011, gate1_true_nand_true) {
  C4011 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): T NAND T = F");
}

Test(c4011, gate1_false_nand_false) {
  C4011 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), True, "Gate1 (pins 1,2->3): F NAND F = T");
}

Test(c4011, gate2_nand) {
  C4011 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = False;
  chip.setLink(5, a, 1);
  chip.setLink(6, b, 1);
  cr_assert_eq(chip.compute(4), True, "Gate2 (pins 5,6->4): T NAND F = T");
}

Test(c4011, gate3_nand) {
  C4011 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(8, a, 1);
  chip.setLink(9, b, 1);
  cr_assert_eq(chip.compute(10), False, "Gate3 (pins 8,9->10): T NAND T = F");
}

Test(c4011, gate4_nand) {
  C4011 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(12, a, 1);
  chip.setLink(13, b, 1);
  cr_assert_eq(chip.compute(11), True, "Gate4 (pins 12,13->11): F NAND F = T");
}

Test(c4011, simulate_no_crash) {
  C4011 chip("chip");
  chip.simulate(1);
  cr_assert(true, "simulate() should not throw");
}

Test(c4011, invalid_pin_throws) {
  C4011 chip("chip");
  bool threw = false;
  try { chip.compute(0); } catch (const NtsException &) { threw = true; }
  cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4030, power_pins_throw) {
  C4030 chip("chip");
  bool t7 = false, t14 = false;
  try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
  try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
  cr_assert(t7,  "Pin 7 (VSS) must throw");
  cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4030, gate1_true_xor_true) {
  C4030 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): T XOR T = F");
}

Test(c4030, gate1_true_xor_false) {
  C4030 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), True, "Gate1 (pins 1,2->3): T XOR F = T");
}

Test(c4030, gate1_false_xor_false) {
  C4030 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): F XOR F = F");
}

Test(c4030, gate2_xor) {
  C4030 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = False;
  chip.setLink(5, a, 1);
  chip.setLink(6, b, 1);
  cr_assert_eq(chip.compute(4), True, "Gate2 (pins 5,6->4): T XOR F = T");
}

Test(c4030, gate3_xor) {
  C4030 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(8, a, 1);
  chip.setLink(9, b, 1);
  cr_assert_eq(chip.compute(10), False, "Gate3 (pins 8,9->10): F XOR F = F");
}

Test(c4030, gate4_xor) {
  C4030 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(12, a, 1);
  chip.setLink(13, b, 1);
  cr_assert_eq(chip.compute(11), False, "Gate4 (pins 12,13->11): T XOR T = F");
}

Test(c4030, simulate_no_crash) {
  C4030 chip("chip");
  chip.simulate(1);
  cr_assert(true, "simulate() should not throw");
}

Test(c4030, invalid_pin_throws) {
  C4030 chip("chip");
  bool threw = false;
  try { chip.compute(0); } catch (const NtsException &) { threw = true; }
  cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4069, power_pins_throw) {
  C4069 chip("chip");
  bool t7 = false, t14 = false;
  try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
  try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
  cr_assert(t7,  "Pin 7 (VSS) must throw");
  cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4069, gate1_not_true) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = True;
  chip.setLink(1, src, 1);
  cr_assert_eq(chip.compute(2), False, "Gate1 (pin 1->2): NOT True = False");
}

Test(c4069, gate1_not_false) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = False;
  chip.setLink(1, src, 1);
  cr_assert_eq(chip.compute(2), True, "Gate1 (pin 1->2): NOT False = True");
}

Test(c4069, gate1_not_undefined) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = Undefined;
  chip.setLink(1, src, 1);
  cr_assert_eq(chip.compute(2), Undefined, "Gate1 (pin 1->2): NOT Undefined = Undefined");
}

Test(c4069, gate2_not) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = True;
  chip.setLink(3, src, 1);
  cr_assert_eq(chip.compute(4), False, "Gate2 (pin 3->4): NOT True = False");
}

Test(c4069, gate3_not) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = False;
  chip.setLink(5, src, 1);
  cr_assert_eq(chip.compute(6), True, "Gate3 (pin 5->6): NOT False = True");
}

Test(c4069, gate4_not) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = True;
  chip.setLink(9, src, 1);
  cr_assert_eq(chip.compute(8), False, "Gate4 (pin 9->8): NOT True = False");
}

Test(c4069, gate5_not) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = False;
  chip.setLink(11, src, 1);
  cr_assert_eq(chip.compute(10), True, "Gate5 (pin 11->10): NOT False = True");
}

Test(c4069, gate6_not) {
  C4069 chip("chip");
  TestableComponent src;
  src.value = True;
  chip.setLink(13, src, 1);
  cr_assert_eq(chip.compute(12), False, "Gate6 (pin 13->12): NOT True = False");
}

Test(c4069, simulate_no_crash) {
  C4069 chip("chip");
  chip.simulate(1);
  cr_assert(true, "simulate() should not throw");
}

Test(c4069, invalid_pin_throws) {
  C4069 chip("chip");
  bool threw = false;
  try { chip.compute(0); } catch (const NtsException &) { threw = true; }
  cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4071, power_pins_throw) {
  C4071 chip("chip");
  bool t7 = false, t14 = false;
  try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
  try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
  cr_assert(t7,  "Pin 7 (VSS) must throw");
  cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4071, gate1_true_or_false) {
  C4071 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), True, "Gate1 (pins 1,2->3): T OR F = T");
}

Test(c4071, gate1_false_or_false) {
  C4071 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): F OR F = F");
}

Test(c4071, gate1_true_or_true) {
  C4071 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), True, "Gate1 (pins 1,2->3): T OR T = T");
}

Test(c4071, gate2_or) {
  C4071 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(5, a, 1);
  chip.setLink(6, b, 1);
  cr_assert_eq(chip.compute(4), True, "Gate2 (pins 5,6->4): T OR T = T");
}

Test(c4071, gate3_or) {
  C4071 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = True;
  chip.setLink(8, a, 1);
  chip.setLink(9, b, 1);
  cr_assert_eq(chip.compute(10), True, "Gate3 (pins 8,9->10): F OR T = T");
}

Test(c4071, gate4_or) {
  C4071 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(12, a, 1);
  chip.setLink(13, b, 1);
  cr_assert_eq(chip.compute(11), False, "Gate4 (pins 12,13->11): F OR F = F");
}

Test(c4071, simulate_no_crash) {
  C4071 chip("chip");
  chip.simulate(1);
  cr_assert(true, "simulate() should not throw");
}

Test(c4071, invalid_pin_throws) {
  C4071 chip("chip");
  bool threw = false;
  try { chip.compute(0); } catch (const NtsException &) { threw = true; }
  cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4081, power_pins_throw) {
  C4081 chip("chip");
  bool t7 = false, t14 = false;
  try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
  try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
  cr_assert(t7,  "Pin 7 (VSS) must throw");
  cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4081, gate1_true_and_true) {
  C4081 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), True, "Gate1 (pins 1,2->3): T AND T = T");
}

Test(c4081, gate1_true_and_false) {
  C4081 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): T AND F = F");
}

Test(c4081, gate1_false_and_false) {
  C4081 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = False;
  chip.setLink(1, a, 1);
  chip.setLink(2, b, 1);
  cr_assert_eq(chip.compute(3), False, "Gate1 (pins 1,2->3): F AND F = F");
}

Test(c4081, gate2_and) {
  C4081 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(5, a, 1);
  chip.setLink(6, b, 1);
  cr_assert_eq(chip.compute(4), True, "Gate2 (pins 5,6->4): T AND T = T");
}

Test(c4081, gate3_and) {
  C4081 chip("chip");
  TestableComponent a, b;
  a.value = False; b.value = True;
  chip.setLink(8, a, 1);
  chip.setLink(9, b, 1);
  cr_assert_eq(chip.compute(10), False, "Gate3 (pins 8,9->10): F AND T = F");
}

Test(c4081, gate4_and) {
  C4081 chip("chip");
  TestableComponent a, b;
  a.value = True; b.value = True;
  chip.setLink(12, a, 1);
  chip.setLink(13, b, 1);
  cr_assert_eq(chip.compute(11), True, "Gate4 (pins 12,13->11): T AND T = T");
}

Test(c4081, simulate_no_crash) {
  C4081 chip("chip");
  chip.simulate(1);
  cr_assert(true, "simulate() should not throw");
}

Test(c4081, invalid_pin_throws) {
  C4081 chip("chip");
  bool threw = false;
  try { chip.compute(0); } catch (const NtsException &) { threw = true; }
  cr_assert(threw, "Pin 0 must throw NtsException");
}

TestableComponent *wirePin(AComponent &chip, std::size_t chipPin)
{
    auto *src = new TestableComponent();
    chip.setLink(chipPin, *src, 1);
    return src;
}

Test(c4008, power_pins_throw) {
    C4008 chip("chip");
    bool t8 = false, t16 = false;
    try { chip.compute(8);  } catch (const NtsException &) { t8  = true; }
    try { chip.compute(16); } catch (const NtsException &) { t16 = true; }
    cr_assert(t8,  "Pin 8 (VSS) must throw");
    cr_assert(t16, "Pin 16 (VDD) must throw");
}

Test(c4008, invalid_pin_throws) {
    C4008 chip("chip");
    bool thrown = false;
    try { chip.compute(0); } catch (const NtsException &) { thrown = true; }
    cr_assert(thrown, "Pin 0 must throw");
}

Test(c4008, zero_plus_zero_no_carry) {
    C4008 chip("chip");
    std::size_t aPins[]   = {7, 5, 3, 1};
    std::size_t bPins[]   = {6, 4, 2, 15};
    for (auto p : aPins) { auto *s = wirePin(chip, p); s->value = False; }
    for (auto p : bPins) { auto *s = wirePin(chip, p); s->value = False; }
    auto *cin = wirePin(chip, 9); cin->value = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(10), False, "Sum0 must be 0");
    cr_assert_eq(chip.compute(11), False, "Sum1 must be 0");
    cr_assert_eq(chip.compute(12), False, "Sum2 must be 0");
    cr_assert_eq(chip.compute(13), False, "Sum3 must be 0");
    cr_assert_eq(chip.compute(14), False, "Cout must be 0");
}

Test(c4008, one_plus_one_no_carry) {
    C4008 chip("chip");
    std::size_t aPins[] = {7, 5, 3, 1};
    std::size_t bPins[] = {6, 4, 2, 15};

    for (int i = 0; i < 4; i++) {
        auto *sa = wirePin(chip, aPins[i]); sa->value = (i == 3) ? True : False;
        auto *sb = wirePin(chip, bPins[i]); sb->value = (i == 3) ? True : False;
    }
    auto *cin = wirePin(chip, 9); cin->value = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(10), False, "Sum0 must be 0");
    cr_assert_eq(chip.compute(11), True,  "Sum1 must be 1");
    cr_assert_eq(chip.compute(12), False, "Sum2 must be 0");
    cr_assert_eq(chip.compute(13), False, "Sum3 must be 0");
    cr_assert_eq(chip.compute(14), False, "Cout must be 0");
}

Test(c4008, all_ones_with_carry_in) {
    C4008 chip("chip");
    std::size_t aPins[] = {7, 5, 3, 1};
    std::size_t bPins[] = {6, 4, 2, 15};
    for (auto p : aPins) { auto *s = wirePin(chip, p); s->value = True; }
    for (auto p : bPins) { auto *s = wirePin(chip, p); s->value = True; }
    auto *cin = wirePin(chip, 9); cin->value = True;

    chip.simulate(1);

    cr_assert_eq(chip.compute(10), True, "Sum0 must be 1");
    cr_assert_eq(chip.compute(11), True, "Sum1 must be 1");
    cr_assert_eq(chip.compute(12), True, "Sum2 must be 1");
    cr_assert_eq(chip.compute(13), True, "Sum3 must be 1");
    cr_assert_eq(chip.compute(14), True, "Cout must be 1");
}

Test(c4008, undefined_input_propagates) {
    C4008 chip("chip");
    std::size_t aPins[] = {7, 5, 3, 1};
    std::size_t bPins[] = {6, 4, 2, 15};
    for (auto p : aPins) { auto *s = wirePin(chip, p); s->value = Undefined; }
    for (auto p : bPins) { auto *s = wirePin(chip, p); s->value = False; }
    auto *cin = wirePin(chip, 9); cin->value = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(10), Undefined, "Sum0 must be Undefined with undefined inputs");
}

Test(c4008, input_pin_passthrough) {
    C4008 chip("chip");
    auto *src = wirePin(chip, 1); src->value = True;
    cr_assert_eq(chip.compute(1), True, "Input pin 1 must return linked value");
}

Test(c4013, power_pins_throw) {
    C4013 chip("chip");
    bool t7 = false, t14 = false;
    try { chip.compute(7);  } catch (const NtsException &) { t7  = true; }
    try { chip.compute(14); } catch (const NtsException &) { t14 = true; }
    cr_assert(t7,  "Pin 7 (VSS) must throw");
    cr_assert(t14, "Pin 14 (VDD) must throw");
}

Test(c4013, ff1_set_dominates_reset) {
    C4013 chip("chip");
    auto *s = wirePin(chip, 6); s->value = True;
    auto *r = wirePin(chip, 4); r->value = True;
    auto *clk = wirePin(chip, 3); clk->value = False;
    auto *d = wirePin(chip, 5); d->value = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(1), True,  "FF1 Q must be 1 when Set");
    cr_assert_eq(chip.compute(2), False, "FF1 Qbar must be 0 when Set");
}

Test(c4013, ff1_reset_clears_q) {
    C4013 chip("chip");
    auto *s = wirePin(chip, 6); s->value = False;
    auto *r = wirePin(chip, 4); r->value = True;
    auto *clk = wirePin(chip, 3); clk->value = False;
    auto *d = wirePin(chip, 5); d->value = True;

    chip.simulate(1);

    cr_assert_eq(chip.compute(1), False, "FF1 Q must be 0 when Reset");
    cr_assert_eq(chip.compute(2), True,  "FF1 Qbar must be 1 when Reset");
}

Test(c4013, ff1_rising_edge_captures_d) {
    C4013 chip("chip");
    auto *s = wirePin(chip, 6); s->value = False;
    auto *r = wirePin(chip, 4); r->value = False;
    auto *clk = wirePin(chip, 3); clk->value = False;
    auto *d = wirePin(chip, 5); d->value = True;

    chip.simulate(1);
    cr_assert_eq(chip.compute(1), Undefined, "Q before first rising edge");

    clk->value = True;
    chip.simulate(2);
    cr_assert_eq(chip.compute(1), True,  "FF1 Q must capture D=1 on rising edge");
    cr_assert_eq(chip.compute(2), False, "FF1 Qbar must be NOT Q");
}

Test(c4013, ff1_no_capture_on_falling_edge) {
    C4013 chip("chip");
    auto *s = wirePin(chip, 6); s->value = False;
    auto *r = wirePin(chip, 4); r->value = False;
    auto *clk = wirePin(chip, 3); clk->value = False;
    auto *d = wirePin(chip, 5); d->value = True;

    clk->value = True;
    chip.simulate(1);

    d->value = False;
    clk->value = False;
    chip.simulate(2);

    cr_assert_eq(chip.compute(1), True, "FF1 Q must not change on falling edge");
}

Test(c4013, ff2_independent_of_ff1) {
    C4013 chip("chip");
    auto *s1 = wirePin(chip, 6); s1->value = False;
    auto *r1 = wirePin(chip, 4); r1->value = False;
    auto *clk1 = wirePin(chip, 3); clk1->value = False;
    auto *d1 = wirePin(chip, 5); d1->value = False;

    auto *s2 = wirePin(chip, 8); s2->value = False;
    auto *r2 = wirePin(chip, 10); r2->value = False;
    auto *clk2 = wirePin(chip, 11); clk2->value = False;
    auto *d2 = wirePin(chip, 9); d2->value = True;

    chip.simulate(1);
    clk2->value = True;
    chip.simulate(2);

    cr_assert_eq(chip.compute(13), True, "FF2 Q must capture D=1");
    cr_assert_eq(chip.compute(1),  Undefined, "FF1 Q unaffected");
}

Test(c4013, ff2_set_forces_q) {
    C4013 chip("chip");
    auto *s2  = wirePin(chip,  8); s2->value  = True;
    auto *r2  = wirePin(chip, 10); r2->value  = False;
    auto *clk2 = wirePin(chip, 11); clk2->value = False;
    auto *d2  = wirePin(chip,  9); d2->value  = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(13), True,  "FF2 Q must be 1 when Set");
    cr_assert_eq(chip.compute(12), False, "FF2 Qbar must be 0 when Set");
}

Test(c4013, ff2_reset_clears_q) {
    C4013 chip("chip");
    auto *s2  = wirePin(chip,  8); s2->value  = False;
    auto *r2  = wirePin(chip, 10); r2->value  = True;
    auto *clk2 = wirePin(chip, 11); clk2->value = False;
    auto *d2  = wirePin(chip,  9); d2->value  = True;

    chip.simulate(1);

    cr_assert_eq(chip.compute(13), False, "FF2 Q must be 0 when Reset");
    cr_assert_eq(chip.compute(12), True,  "FF2 Qbar must be 1 when Reset");
}

Test(c4013, input_pin_passthrough) {
    C4013 chip("chip");
    auto *clk = wirePin(chip, 3); clk->value = True;
    cr_assert_eq(chip.compute(3), True, "Input pin 3 must return linked value");
}

Test(c4013, invalid_pin_throws) {
    C4013 chip("chip");
    bool threw = false;
    try { chip.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4017, power_pins_throw) {
    C4017 chip("chip");
    bool t8 = false, t16 = false;
    try { chip.compute(8);  } catch (const NtsException &) { t8  = true; }
    try { chip.compute(16); } catch (const NtsException &) { t16 = true; }
    cr_assert(t8,  "Pin 8 must throw");
    cr_assert(t16, "Pin 16 must throw");
}

Test(c4017, reset_forces_q0) {
    C4017 chip("chip");
    auto *clk   = wirePin(chip, 14); clk->value = False;
    auto *inh   = wirePin(chip, 13); inh->value = False;
    auto *reset = wirePin(chip, 15); reset->value = True;

    chip.simulate(1);

    cr_assert_eq(chip.compute(3),  True,  "Q0 (pin 3) must be True after reset");
    cr_assert_eq(chip.compute(2),  False, "Q1 (pin 2) must be False after reset");
    cr_assert_eq(chip.compute(12), False, "CarryOut must be False at count 0");
}

Test(c4017, counts_on_rising_edge) {
    C4017 chip("chip");
    auto *clk   = wirePin(chip, 14); clk->value = False;
    auto *inh   = wirePin(chip, 13); inh->value = False;
    auto *reset = wirePin(chip, 15); reset->value = True;

    chip.simulate(1);
    reset->value = False;

    static const std::size_t qPins[] = {3, 2, 4, 7, 10, 1, 5, 6, 9, 11};

    for (int edge = 0; edge < 3; edge++) {
        clk->value = True;
        chip.simulate(edge * 2 + 2);
        clk->value = False;
        chip.simulate(edge * 2 + 3);

        for (int q = 0; q < 10; q++) {
            Tristate expected = (q == edge + 1) ? True : False;
            cr_assert_eq(chip.compute(qPins[q]), expected,
                "After edge %d: Q%d mismatch", edge + 1, q);
        }
    }
}

Test(c4017, inhibit_blocks_counting) {
    C4017 chip("chip");
    auto *clk   = wirePin(chip, 14); clk->value = False;
    auto *inh   = wirePin(chip, 13); inh->value = False;
    auto *reset = wirePin(chip, 15); reset->value = True;

    chip.simulate(1);
    reset->value = False;

    clk->value = True; chip.simulate(2);
    clk->value = False; chip.simulate(3);

    inh->value = True;

    clk->value = True; chip.simulate(4);
    clk->value = False; chip.simulate(5);
    clk->value = True; chip.simulate(6);
    clk->value = False; chip.simulate(7);

    cr_assert_eq(chip.compute(2), True,  "Q1 must stay True while inhibited");
    cr_assert_eq(chip.compute(4), False, "Q2 must remain False while inhibited");
}

Test(c4017, no_spurious_edge_after_inhibit) {
    C4017 chip("chip");
    auto *clk   = wirePin(chip, 14); clk->value = False;
    auto *inh   = wirePin(chip, 13); inh->value = False;
    auto *reset = wirePin(chip, 15); reset->value = True;

    chip.simulate(1);
    reset->value = False;

    clk->value = True; chip.simulate(2);
    clk->value = False; chip.simulate(3);

    inh->value = True;
    clk->value = True; chip.simulate(4);

    inh->value = False;
    chip.simulate(5);

    cr_assert_eq(chip.compute(2), True,  "Q1 must still be True (no spurious advance)");
    cr_assert_eq(chip.compute(4), False, "Q2 must remain False (no spurious advance)");
}

Test(c4017, carry_out_high_for_counts_0_to_4) {
    C4017 chip("chip");
    auto *clk   = wirePin(chip, 14); clk->value = False;
    auto *inh   = wirePin(chip, 13); inh->value = False;
    auto *reset = wirePin(chip, 15); reset->value = True;

    chip.simulate(1);
    reset->value = False;

    std::size_t tick = 2;
    for (int count = 0; count < 10; count++) {
        Tristate expected = (count < 5) ? True : False;
        cr_assert_eq(chip.compute(12), expected,
            "CarryOut mismatch at count %d", count);

        clk->value = True;  chip.simulate(tick++);
        clk->value = False; chip.simulate(tick++);
    }
}

Test(c4017, input_pin_passthrough) {
    C4017 chip("chip");
    auto *clk = wirePin(chip, 14); clk->value = True;
    cr_assert_eq(chip.compute(14), True,  "Input pin 14 must return linked value");
    auto *inh = wirePin(chip, 13); inh->value = False;
    cr_assert_eq(chip.compute(13), False, "Input pin 13 must return linked value");
    auto *rst = wirePin(chip, 15); rst->value = False;
    cr_assert_eq(chip.compute(15), False, "Input pin 15 must return linked value");
}

Test(c4017, invalid_pin_throws) {
    C4017 chip("chip");
    bool threw = false;
    try { chip.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4040, power_pins_throw) {
    C4040 chip("chip");
    bool t8 = false, t16 = false;
    try { chip.compute(8);  } catch (const NtsException &) { t8  = true; }
    try { chip.compute(16); } catch (const NtsException &) { t16 = true; }
    cr_assert(t8,  "Pin 8 must throw");
    cr_assert(t16, "Pin 16 must throw");
}

Test(c4040, reset_clears_counter) {
    C4040 chip("chip");
    auto *clk   = wirePin(chip, 10); clk->value = False;
    auto *reset = wirePin(chip, 11); reset->value = True;

    chip.simulate(1);

    static const std::size_t outPins[] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};
    for (auto p : outPins)
        cr_assert_eq(chip.compute(p), False, "Pin %zu must be 0 after reset", p);
}

Test(c4040, counts_on_falling_edge) {
    C4040 chip("chip");
    auto *clk   = wirePin(chip, 10); clk->value = True;
    auto *reset = wirePin(chip, 11); reset->value = True;

    chip.simulate(1);
    reset->value = False;

    clk->value = False; chip.simulate(2);
    cr_assert_eq(chip.compute(9), True, "Q0 must be 1 after first falling edge");

    clk->value = True; chip.simulate(3);
    cr_assert_eq(chip.compute(9), True, "Q0 must stay 1 on rising edge");

    clk->value = False; chip.simulate(4);
    cr_assert_eq(chip.compute(9), False, "Q0 must be 0 at count 2");
    cr_assert_eq(chip.compute(7), True,  "Q1 must be 1 at count 2");
}

Test(c4040, no_spurious_edge_after_reset) {
    C4040 chip("chip");
    auto *clk   = wirePin(chip, 10); clk->value = True;
    auto *reset = wirePin(chip, 11); reset->value = True;

    chip.simulate(1);
    clk->value = False;
    chip.simulate(2);

    reset->value = False;
    chip.simulate(3);

    static const std::size_t outPins[] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};
    for (auto p : outPins)
        cr_assert_eq(chip.compute(p), False,
            "Pin %zu must be 0 — no spurious count after reset release", p);
}

Test(c4040, wraps_at_4096) {
    C4040 chip("chip");
    auto *clk   = wirePin(chip, 10); clk->value = True;
    auto *reset = wirePin(chip, 11); reset->value = True;

    chip.simulate(1);
    reset->value = False;

    std::size_t tick = 2;
    for (int i = 0; i < 4096; i++) {
        clk->value = False; chip.simulate(tick++);
        clk->value = True;  chip.simulate(tick++);
    }

    static const std::size_t outPins[] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};
    for (auto p : outPins)
        cr_assert_eq(chip.compute(p), False, "Pin %zu must be 0 after wrap-around", p);
}

Test(c4040, input_pin_passthrough) {
    C4040 chip("chip");
    auto *clk = wirePin(chip, 10); clk->value = True;
    cr_assert_eq(chip.compute(10), True,  "Input pin 10 must return linked value");
    auto *rst = wirePin(chip, 11); rst->value = False;
    cr_assert_eq(chip.compute(11), False, "Input pin 11 must return linked value");
}

Test(c4040, invalid_pin_throws) {
    C4040 chip("chip");
    bool threw = false;
    try { chip.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4094, power_pins_throw) {
    C4094 chip("chip");
    bool t8 = false, t16 = false;
    try { chip.compute(8);  } catch (const NtsException &) { t8  = true; }
    try { chip.compute(16); } catch (const NtsException &) { t16 = true; }
    cr_assert(t8,  "Pin 8 must throw");
    cr_assert(t16, "Pin 16 must throw");
}

Test(c4094, output_disabled_when_oe_low) {
    C4094 chip("chip");
    auto *strobe = wirePin(chip, 1); strobe->value = False;
    auto *data   = wirePin(chip, 2); data->value = True;
    auto *clk    = wirePin(chip, 3); clk->value = False;
    auto *oe     = wirePin(chip, 15); oe->value = False;

    chip.simulate(1);

    static const std::size_t outPins[] = {4, 5, 6, 7, 14, 13, 12, 11};
    for (auto p : outPins)
        cr_assert_eq(chip.compute(p), Undefined,
            "Pin %zu must be Undefined when OE=0", p);
}

Test(c4094, shift_and_strobe) {
    C4094 chip("chip");
    auto *strobe = wirePin(chip, 1); strobe->value = False;
    auto *data   = wirePin(chip, 2); data->value = False;
    auto *clk    = wirePin(chip, 3); clk->value = False;
    auto *oe     = wirePin(chip, 15); oe->value = True;

    int pattern[] = {1, 0, 1, 0, 1, 0, 1, 0};
    std::size_t tick = 1;

    for (int i = 0; i < 8; i++) {
        data->value = pattern[i] ? True : False;
        clk->value  = True;  chip.simulate(tick++);
        clk->value  = False; chip.simulate(tick++);
    }

    strobe->value = True;
    chip.simulate(tick++);

    static const std::size_t outPins[] = {4, 5, 6, 7, 14, 13, 12, 11};
    for (int i = 0; i < 8; i++) {
        Tristate expected = pattern[i] ? True : False;
        cr_assert_eq(chip.compute(outPins[i]), expected,
            "Output %d mismatch after strobe", i);
    }
}

Test(c4094, qs_serial_output) {
    C4094 chip("chip");
    auto *strobe = wirePin(chip, 1); strobe->value = False;
    auto *data   = wirePin(chip, 2); data->value = True;
    auto *clk    = wirePin(chip, 3); clk->value = False;
    auto *oe     = wirePin(chip, 15); oe->value = True;

    std::size_t tick = 1;
    for (int i = 0; i < 8; i++) {
        clk->value = True;  chip.simulate(tick++);
        clk->value = False; chip.simulate(tick++);
    }
    cr_assert_eq(chip.compute(9), True, "Qs (pin9) must reflect register[7]");
}

Test(c4094, input_pin_passthrough) {
    C4094 chip("chip");
    auto *strobe = wirePin(chip, 1); strobe->value = True;
    cr_assert_eq(chip.compute(1), True, "Input pin 1 must return linked value");
    auto *oe = wirePin(chip, 15); oe->value = False;
    cr_assert_eq(chip.compute(15), False, "Input pin 15 must return linked value");
}

Test(c4094, qs_prime_serial_output) {
    C4094 chip("chip");
    auto *strobe = wirePin(chip, 1); strobe->value = False;
    auto *data   = wirePin(chip, 2); data->value = True;
    auto *clk    = wirePin(chip, 3); clk->value = False;
    auto *oe     = wirePin(chip, 15); oe->value = True;

    std::size_t tick = 1;
    for (int i = 0; i < 8; i++) {
        clk->value = True;  chip.simulate(tick++);
        clk->value = False; chip.simulate(tick++);
    }
    strobe->value = True;
    chip.simulate(tick++);

    cr_assert_eq(chip.compute(10), True, "Qs' (pin 10) must reflect registers_next[7]");
}

Test(c4094, invalid_pin_throws) {
    C4094 chip("chip");
    auto *oe = wirePin(chip, 15); oe->value = True;
    bool threw = false;
    try { chip.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4512, power_pins_throw) {
    C4512 chip("chip");
    bool t8 = false, t16 = false;
    try { chip.compute(8);  } catch (const NtsException &) { t8  = true; }
    try { chip.compute(16); } catch (const NtsException &) { t16 = true; }
    cr_assert(t8,  "Pin 8 must throw");
    cr_assert(t16, "Pin 16 must throw");
}

Test(c4512, inhibit_forces_output_low) {
    C4512 chip("chip");
    auto *inh = wirePin(chip, 10); inh->value = True;
    auto *en  = wirePin(chip, 15); en->value  = True;
    auto *a   = wirePin(chip, 11); a->value   = False;
    auto *b   = wirePin(chip, 12); b->value   = False;
    auto *c   = wirePin(chip, 13); c->value   = False;
    auto *d0  = wirePin(chip,  1); d0->value  = True;

    cr_assert_eq(chip.compute(14), False, "Output must be False when inhibited");
}

Test(c4512, enable_false_gives_undefined) {
    C4512 chip("chip");
    auto *inh = wirePin(chip, 10); inh->value = False;
    auto *en  = wirePin(chip, 15); en->value  = False;
    auto *a   = wirePin(chip, 11); a->value   = False;
    auto *b   = wirePin(chip, 12); b->value   = False;
    auto *c   = wirePin(chip, 13); c->value   = False;

    cr_assert_eq(chip.compute(14), Undefined, "Output must be Undefined when EN=0");
}

Test(c4512, selects_channel_0) {
    C4512 chip("chip");
    auto *inh = wirePin(chip, 10); inh->value = False;
    auto *en  = wirePin(chip, 15); en->value  = True;
    auto *a   = wirePin(chip, 11); a->value   = False;
    auto *b   = wirePin(chip, 12); b->value   = False;
    auto *c   = wirePin(chip, 13); c->value   = False;
    auto *d0  = wirePin(chip,  1); d0->value  = True;

    cr_assert_eq(chip.compute(14), True, "Channel 0 (pin 1) must be selected");
}

Test(c4512, selects_channel_7) {
    C4512 chip("chip");
    auto *inh = wirePin(chip, 10); inh->value = False;
    auto *en  = wirePin(chip, 15); en->value  = True;
    auto *a   = wirePin(chip, 11); a->value   = True;
    auto *b   = wirePin(chip, 12); b->value   = True;
    auto *c   = wirePin(chip, 13); c->value   = True;
    auto *d7  = wirePin(chip,  9); d7->value  = True;
    for (std::size_t p : {1u,2u,3u,4u,5u,6u,7u}) {
        auto *s = wirePin(chip, p); s->value = False;
    }

    cr_assert_eq(chip.compute(14), True, "Channel 7 (pin 9) must be selected");
}

Test(c4514, power_pins_throw) {
    C4514 chip("chip");
    bool t12 = false, t24 = false;
    try { chip.compute(12); } catch (const NtsException &) { t12 = true; }
    try { chip.compute(24); } catch (const NtsException &) { t24 = true; }
    cr_assert(t12, "Pin 12 must throw");
    cr_assert(t24, "Pin 24 must throw");
}

Test(c4514, inhibit_forces_all_outputs_low) {
    C4514 chip("chip");
    auto *inh    = wirePin(chip, 23); inh->value = True;
    auto *strobe = wirePin(chip,  1); strobe->value = True;
    auto *a0     = wirePin(chip,  2); a0->value  = False;
    auto *a1     = wirePin(chip,  3); a1->value  = False;
    auto *a2     = wirePin(chip, 21); a2->value  = False;
    auto *a3     = wirePin(chip, 22); a3->value  = False;

    chip.simulate(1);

    static const std::size_t outPins[] = {
        11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15
    };
    for (auto p : outPins)
        cr_assert_eq(chip.compute(p), False, "Pin %zu must be False when inhibited", p);
}

Test(c4514, selects_output_0) {
    C4514 chip("chip");
    auto *inh    = wirePin(chip, 23); inh->value = False;
    auto *strobe = wirePin(chip,  1); strobe->value = True;
    auto *a0     = wirePin(chip,  2); a0->value  = False;
    auto *a1     = wirePin(chip,  3); a1->value  = False;
    auto *a2     = wirePin(chip, 21); a2->value  = False;
    auto *a3     = wirePin(chip, 22); a3->value  = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(11), True, "Output 0 (pin 11) must be True");
    cr_assert_eq(chip.compute(9),  False, "Output 1 (pin 9) must be False");
}

Test(c4514, selects_output_15) {
    C4514 chip("chip");
    auto *inh    = wirePin(chip, 23); inh->value = False;
    auto *strobe = wirePin(chip,  1); strobe->value = True;
    auto *a0     = wirePin(chip,  2); a0->value  = True;
    auto *a1     = wirePin(chip,  3); a1->value  = True;
    auto *a2     = wirePin(chip, 21); a2->value  = True;
    auto *a3     = wirePin(chip, 22); a3->value  = True;

    chip.simulate(1);

    static const std::size_t outPins[] = {
        11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15
    };
    for (int i = 0; i < 15; i++)
        cr_assert_eq(chip.compute(outPins[i]), False, "Output %d must be False", i);
    cr_assert_eq(chip.compute(outPins[15]), True, "Output 15 (pin 15) must be True");
}

Test(c4514, strobe_latches_address) {
    C4514 chip("chip");
    auto *inh    = wirePin(chip, 23); inh->value = False;
    auto *strobe = wirePin(chip,  1); strobe->value = True;
    auto *a0     = wirePin(chip,  2); a0->value  = False;
    auto *a1     = wirePin(chip,  3); a1->value  = False;
    auto *a2     = wirePin(chip, 21); a2->value  = False;
    auto *a3     = wirePin(chip, 22); a3->value  = False;

    chip.simulate(1);

    strobe->value = False;
    a0->value = True;
    chip.simulate(2);

    cr_assert_eq(chip.compute(11), True,  "Output 0 must stay latched");
    cr_assert_eq(chip.compute(9),  False, "Output 1 must stay False");
}

Test(c4514, undefined_address_gives_undefined_output) {
    C4514 chip("chip");
    auto *inh    = wirePin(chip, 23); inh->value = False;
    auto *strobe = wirePin(chip,  1); strobe->value = True;
    auto *a0     = wirePin(chip,  2); a0->value  = Undefined;
    auto *a1     = wirePin(chip,  3); a1->value  = False;
    auto *a2     = wirePin(chip, 21); a2->value  = False;
    auto *a3     = wirePin(chip, 22); a3->value  = False;

    chip.simulate(1);

    cr_assert_eq(chip.compute(11), Undefined,
        "Output must be Undefined when latched address is Undefined");
}

Test(c4514, input_pin_passthrough) {
    C4514 chip("chip");
    auto *a0 = wirePin(chip, 2); a0->value = True;
    cr_assert_eq(chip.compute(2), True, "Input pin 2 must return linked value");
}

Test(c4514, invalid_pin_throws) {
    C4514 chip("chip");
    bool threw = false;
    try { chip.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "Pin 0 must throw NtsException");
}

Test(c4801, power_pins_throw) {
    C4801 chip("chip");
    bool t12 = false, t19 = false, t24 = false;
    try { chip.compute(12); } catch (const NtsException &) { t12 = true; }
    try { chip.compute(19); } catch (const NtsException &) { t19 = true; }
    try { chip.compute(24); } catch (const NtsException &) { t24 = true; }
    cr_assert(t12, "Pin 12 must throw");
    cr_assert(t19, "Pin 19 must throw");
    cr_assert(t24, "Pin 24 must throw");
}

Test(c4801, output_disabled_without_oe) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    auto *we = wirePin(chip, 21); we->value = False;
    auto *oe = wirePin(chip, 20); oe->value = False;

    for (std::size_t p : {8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u}) {
        auto *s = wirePin(chip, p); s->value = False;
    }
    chip.simulate(1);

    static const std::size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
    for (auto p : dataPins)
        cr_assert_eq(chip.compute(p), Undefined,
            "Pin %zu must be Undefined when OE=0", p);
}

Test(c4801, write_then_read) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    auto *we = wirePin(chip, 21); we->value = True;
    auto *oe = wirePin(chip, 20); oe->value = False;

    std::size_t addrPins[] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
    for (auto p : addrPins) { auto *s = wirePin(chip, p); s->value = False; }

    std::size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
    for (auto p : dataPins) { auto *s = wirePin(chip, p); s->value = True; }

    chip.simulate(1);
    chip.simulate(2);

    we->value = False;
    oe->value = True;
    chip.simulate(3);

    for (auto p : dataPins)
        cr_assert_eq(chip.compute(p), True, "Data pin %zu must be 1 after write 0xFF", p);
}

Test(c4801, read_unwritten_returns_zero) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    auto *we = wirePin(chip, 21); we->value = False;
    auto *oe = wirePin(chip, 20); oe->value = True;

    std::size_t addrPins[] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
    for (auto p : addrPins) { auto *s = wirePin(chip, p); s->value = False; }

    chip.simulate(1);

    std::size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
    for (auto p : dataPins)
        cr_assert_eq(chip.compute(p), False,
            "Data pin %zu must be 0 for unwritten address", p);
}

Test(c4801, simulate_aborts_on_undefined_address_bit) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    auto *we = wirePin(chip, 21); we->value = True;
    auto *oe = wirePin(chip, 20); oe->value = False;

    auto *a0 = wirePin(chip, 8); a0->value = Undefined;
    for (std::size_t p : {7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u}) {
        auto *s = wirePin(chip, p); s->value = False;
    }
    std::size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
    for (auto p : dataPins) { auto *d = wirePin(chip, p); d->value = True; }

    chip.simulate(1);
    chip.simulate(2);

    a0->value = False;
    we->value = False;
    oe->value = True;
    chip.simulate(3);

    for (auto p : dataPins)
        cr_assert_eq(chip.compute(p), False,
            "Memory must not be written when address bit is Undefined");
}

Test(c4801, write_to_nonzero_address) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    auto *we = wirePin(chip, 21); we->value = True;
    auto *oe = wirePin(chip, 20); oe->value = False;

    auto *a0 = wirePin(chip, 8); a0->value = True;
    for (std::size_t p : {7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u}) {
        auto *s = wirePin(chip, p); s->value = False;
    }
    std::size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
    for (auto p : dataPins) { auto *d = wirePin(chip, p); d->value = True; }

    chip.simulate(1);
    chip.simulate(2);

    we->value = False;
    oe->value = True;
    chip.simulate(3);

    for (auto p : dataPins)
        cr_assert_eq(chip.compute(p), True,
            "Data pin %zu must be 1 at address 1 after write", p);
}

Test(c4801, input_pin_passthrough) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    cr_assert_eq(chip.compute(18), True, "Input pin 18 must return linked value");
}

Test(c4801, compute_data_pin_cs_disabled_returns_undefined) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = False;
    auto *oe = wirePin(chip, 20); oe->value = True;
    auto *we = wirePin(chip, 21); we->value = False;
    for (std::size_t p : {8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u}) {
        auto *s = wirePin(chip, p); s->value = False;
    }
    chip.simulate(1);
    cr_assert_eq(chip.compute(9), Undefined,
        "Data pin must be Undefined when CS is disabled");
}

Test(c4801, compute_data_pin_undefined_address_returns_undefined) {
    C4801 chip("chip");
    auto *cs = wirePin(chip, 18); cs->value = True;
    auto *oe = wirePin(chip, 20); oe->value = True;
    auto *we = wirePin(chip, 21); we->value = False;
    auto *a0 = wirePin(chip, 8); a0->value = Undefined;
    for (std::size_t p : {7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u}) {
        auto *s = wirePin(chip, p); s->value = False;
    }
    chip.simulate(1);
    cr_assert_eq(chip.compute(9), Undefined,
        "Data pin must be Undefined when address bit is Undefined");
}

Test(c4801, invalid_pin_throws) {
    C4801 chip("chip");
    bool threw = false;
    try { chip.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "Pin 0 must throw NtsException");
}

static std::vector<unsigned char> readLogFile()
{
    std::ifstream f("./log.bin", std::ios::binary);
    return std::vector<unsigned char>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>());
}

Test(logger, invalid_pin_zero_throws) {
    std::remove("./log.bin");
    Logger logger("logger");
    bool threw = false;
    try { logger.compute(0); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "compute(0) must throw NtsException");
}

Test(logger, invalid_pin_eleven_throws) {
    std::remove("./log.bin");
    Logger logger("logger");
    bool threw = false;
    try { logger.compute(11); } catch (const NtsException &) { threw = true; }
    cr_assert(threw, "compute(11) must throw NtsException");
}

Test(logger, compute_valid_pin_returns_link) {
    std::remove("./log.bin");
    Logger logger("logger");
    auto *d0 = wirePin(logger, 1); d0->value = True;
    cr_assert_eq(logger.compute(1), True, "compute(1) must return the linked value");
}

Test(logger, no_write_without_rising_edge) {
    std::remove("./log.bin");
    Logger logger("logger");
    auto *clk = wirePin(logger, 9);  clk->value = False;
    auto *inh = wirePin(logger, 10); inh->value = False;
    for (std::size_t i = 1; i <= 8; i++) { auto *d = wirePin(logger, i); d->value = True; }

    logger.simulate(1);

    auto data = readLogFile();
    cr_assert_eq(data.size(), 0u, "No byte should be written when clock never rises");
}

Test(logger, write_on_rising_edge_byte_d0) {
    std::remove("./log.bin");
    Logger logger("logger");
    auto *clk = wirePin(logger, 9);  clk->value = False;
    auto *inh = wirePin(logger, 10); inh->value = False;
    auto *d0 = wirePin(logger, 1); d0->value = True;
    for (std::size_t i = 2; i <= 8; i++) { auto *d = wirePin(logger, i); d->value = False; }

    logger.simulate(1);
    clk->value = True;
    logger.simulate(2);

    auto data = readLogFile();
    cr_assert_eq(data.size(), 1u, "Exactly one byte should be written on rising edge");
    cr_assert_eq(data[0], (unsigned char)0x01, "Written byte should be 0x01 (D0 set)");
}

Test(logger, no_write_when_inhibit_true) {
    std::remove("./log.bin");
    Logger logger("logger");
    auto *clk = wirePin(logger, 9);  clk->value = False;
    auto *inh = wirePin(logger, 10); inh->value = True;
    for (std::size_t i = 1; i <= 8; i++) { auto *d = wirePin(logger, i); d->value = True; }

    logger.simulate(1);
    clk->value = True;
    logger.simulate(2);

    auto data = readLogFile();
    cr_assert_eq(data.size(), 0u, "No byte should be written when inhibit is True");
}

Test(logger, byte_assembly_d7_msb) {
    std::remove("./log.bin");
    Logger logger("logger");
    auto *clk = wirePin(logger, 9);  clk->value = False;
    auto *inh = wirePin(logger, 10); inh->value = False;
    for (std::size_t i = 1; i <= 7; i++) { auto *d = wirePin(logger, i); d->value = False; }
    auto *d7 = wirePin(logger, 8); d7->value = True;

    logger.simulate(1);
    clk->value = True;
    logger.simulate(2);

    auto data = readLogFile();
    cr_assert_eq(data.size(), 1u, "One byte should be written");
    cr_assert_eq(data[0], (unsigned char)0x80, "D7 set only should give byte 0x80");
}

Test(logger, no_double_write_on_sustained_clock_high) {
    std::remove("./log.bin");
    Logger logger("logger");
    auto *clk = wirePin(logger, 9);  clk->value = False;
    auto *inh = wirePin(logger, 10); inh->value = False;
    for (std::size_t i = 1; i <= 8; i++) { auto *d = wirePin(logger, i); d->value = False; }

    logger.simulate(1);
    clk->value = True;
    logger.simulate(2);
    logger.simulate(3);

    auto data = readLogFile();
    cr_assert_eq(data.size(), 1u, "Only one byte written for sustained high clock");
}

Test(component_factory, sets_name_on_created_component) {
    ComponentFactory factory;
    auto comp = factory.createComponent("input", "my_input");
    auto *base = dynamic_cast<AComponent *>(comp.get());
    cr_assert_not_null(base);
    cr_assert_str_eq(base->getName().c_str(), "my_input",
        "createComponent should assign the given name to the component");
}

Test(component_factory, unknown_type_throws_nts_exception) {
    ComponentFactory factory;
    cr_assert_throw(factory.createComponent("does_not_exist", "x"), NtsException,
        "createComponent with an unknown type should throw NtsException");
}

Test(component_factory, empty_type_throws_nts_exception) {
    ComponentFactory factory;
    cr_assert_throw(factory.createComponent("", "x"), NtsException,
        "createComponent with an empty type string should throw NtsException");
}

Test(component_factory, creates_input) {
    ComponentFactory factory;
    auto comp = factory.createComponent("input", "a");
    cr_assert_not_null(dynamic_cast<Input *>(comp.get()),
        "type \"input\" should produce an Input instance");
}

Test(component_factory, creates_output) {
    ComponentFactory factory;
    auto comp = factory.createComponent("output", "a");
    cr_assert_not_null(dynamic_cast<Output *>(comp.get()),
        "type \"output\" should produce an Output instance");
}

Test(component_factory, creates_true) {
    ComponentFactory factory;
    auto comp = factory.createComponent("true", "a");
    cr_assert_not_null(dynamic_cast<TrueComp *>(comp.get()),
        "type \"true\" should produce a TrueComp instance");
}

Test(component_factory, creates_false) {
    ComponentFactory factory;
    auto comp = factory.createComponent("false", "a");
    cr_assert_not_null(dynamic_cast<FalseComp *>(comp.get()),
        "type \"false\" should produce a FalseComp instance");
}

Test(component_factory, creates_clock) {
    ComponentFactory factory;
    auto comp = factory.createComponent("clock", "a");
    cr_assert_not_null(dynamic_cast<Clock *>(comp.get()),
        "type \"clock\" should produce a Clock instance");
}

Test(component_factory, creates_and_gate) {
    ComponentFactory factory;
    auto comp = factory.createComponent("and", "a");
    cr_assert_not_null(dynamic_cast<AndGate *>(comp.get()),
        "type \"and\" should produce an AndGate instance");
}

Test(component_factory, creates_or_gate) {
    ComponentFactory factory;
    auto comp = factory.createComponent("or", "a");
    cr_assert_not_null(dynamic_cast<OrGate *>(comp.get()),
        "type \"or\" should produce an OrGate instance");
}

Test(component_factory, creates_xor_gate) {
    ComponentFactory factory;
    auto comp = factory.createComponent("xor", "a");
    cr_assert_not_null(dynamic_cast<XorGate *>(comp.get()),
        "type \"xor\" should produce an XorGate instance");
}

Test(component_factory, creates_not_gate) {
    ComponentFactory factory;
    auto comp = factory.createComponent("not", "a");
    cr_assert_not_null(dynamic_cast<NotGate *>(comp.get()),
        "type \"not\" should produce a NotGate instance");
}

Test(component_factory, creates_c4001) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4001", "a");
    cr_assert_not_null(dynamic_cast<C4001 *>(comp.get()),
        "type \"4001\" should produce a C4001 instance");
}

Test(component_factory, creates_c4011) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4011", "a");
    cr_assert_not_null(dynamic_cast<C4011 *>(comp.get()),
        "type \"4011\" should produce a C4011 instance");
}

Test(component_factory, creates_c4069) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4069", "a");
    cr_assert_not_null(dynamic_cast<C4069 *>(comp.get()),
        "type \"4069\" should produce a C4069 instance");
}

Test(component_factory, creates_c4008) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4008", "a");
    cr_assert_not_null(dynamic_cast<C4008 *>(comp.get()),
        "type \"4008\" should produce a C4008 instance");
}

Test(component_factory, creates_c4013) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4013", "a");
    cr_assert_not_null(dynamic_cast<C4013 *>(comp.get()),
        "type \"4013\" should produce a C4013 instance");
}

Test(component_factory, creates_c4801) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4801", "a");
    cr_assert_not_null(dynamic_cast<C4801 *>(comp.get()),
        "type \"4801\" should produce a C4801 instance");
}

Test(component_factory, creates_c2716) {
    ComponentFactory factory;
    auto comp = factory.createComponent("2716", "a");
    cr_assert_not_null(dynamic_cast<C2716 *>(comp.get()),
        "type \"2716\" should produce a C2716 instance");
}

Test(component_factory, creates_logger) {
    std::remove("./log.bin");
    ComponentFactory factory;
    auto comp = factory.createComponent("logger", "a");
    cr_assert_not_null(dynamic_cast<Logger *>(comp.get()),
        "type \"logger\" should produce a Logger instance");
}

Test(component_factory, each_call_returns_new_instance) {
    ComponentFactory factory;
    auto a = factory.createComponent("and", "g1");
    auto b = factory.createComponent("and", "g2");
    cr_assert_neq(a.get(), b.get(),
        "each createComponent call should return a distinct object");
}

Test(component_factory, creates_nor_gate) {
    ComponentFactory factory;
    auto comp = factory.createComponent("nor", "g");
    cr_assert_not_null(dynamic_cast<NorGate *>(comp.get()));
}

Test(component_factory, creates_nand_gate) {
    ComponentFactory factory;
    auto comp = factory.createComponent("nand", "g");
    cr_assert_not_null(dynamic_cast<NandGate *>(comp.get()));
}

Test(component_factory, creates_c4030) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4030", "g");
    cr_assert_not_null(dynamic_cast<C4030 *>(comp.get()));
}

Test(component_factory, creates_c4071) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4071", "g");
    cr_assert_not_null(dynamic_cast<C4071 *>(comp.get()));
}

Test(component_factory, creates_c4081) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4081", "g");
    cr_assert_not_null(dynamic_cast<C4081 *>(comp.get()));
}

Test(component_factory, creates_c4017) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4017", "g");
    cr_assert_not_null(dynamic_cast<C4017 *>(comp.get()));
}

Test(component_factory, creates_c4040) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4040", "g");
    cr_assert_not_null(dynamic_cast<C4040 *>(comp.get()));
}

Test(component_factory, creates_c4094) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4094", "g");
    cr_assert_not_null(dynamic_cast<C4094 *>(comp.get()));
}

Test(component_factory, creates_c4512) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4512", "g");
    cr_assert_not_null(dynamic_cast<C4512 *>(comp.get()));
}

Test(component_factory, creates_c4514) {
    ComponentFactory factory;
    auto comp = factory.createComponent("4514", "g");
    cr_assert_not_null(dynamic_cast<C4514 *>(comp.get()));
}

Test(component_factory, unknown_type_throws) {
    ComponentFactory factory;
    bool thrown = false;
    try { (void)factory.createComponent("unknown_xyz", "g"); }
    catch (const NtsException &) { thrown = true; }
    cr_assert(thrown, "Unknown component type should throw NtsException");
}

Test(shell, eof_exits_cleanly, .init = cr_redirect_stdout) {
    Circuit c;
    Shell shell(c);
    std::istringstream mock_input("");
    std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());
    shell.run();
    std::cin.rdbuf(old_cin);
    cr_assert(true, "Shell should exit cleanly on EOF");
}

Test(shell, empty_lines_ignored, .init = cr_redirect_stdout) {
    Circuit c;
    Shell shell(c);
    std::istringstream mock_input("\n\nexit\n");
    std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());
    shell.run();
    std::cin.rdbuf(old_cin);
    cr_assert(true, "Shell should ignore empty lines");
}

Test(shell, cmd_set_input_empty_value_error, .init = cr_redirect_stderr) {
    Circuit c;
    Shell shell(c);
    std::istringstream mock_input("name=\nexit\n");
    std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());
    shell.run();
    std::cin.rdbuf(old_cin);
    cr_assert_stderr_eq_str("Error: Invalid input assignment: 'name='\n");
}

Test(shell, cmd_set_input_starts_with_eq_error, .init = cr_redirect_stderr) {
    Circuit c;
    Shell shell(c);
    std::istringstream mock_input("=1\nexit\n");
    std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());
    shell.run();
    std::cin.rdbuf(old_cin);
    cr_assert_stderr_eq_str("Error: Invalid input assignment: '=1'\n");
}

Test(shell, cmd_loop_exits_on_sigint) {
    Circuit c;
    std::thread t([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        raise(SIGINT);
    });
    Shell shell(c);
    std::istringstream mock_input("loop\nexit\n");
    std::streambuf *old_cin = std::cin.rdbuf(mock_input.rdbuf());
    std::ostringstream discard;
    std::streambuf *old_cout = std::cout.rdbuf(discard.rdbuf());
    shell.run();
    std::cout.rdbuf(old_cout);
    std::cin.rdbuf(old_cin);
    t.join();
    cr_assert(true, "cmdLoop should exit after SIGINT");
}

Test(parser, double_chipsets_throws) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".chipsets:\ninput a\n.chipsets:\n");
    bool thrown = false;
    try { (void)parser.parse(iss); } catch (const ParseError &) { thrown = true; }
    cr_assert(thrown, "Expected ParseError on duplicate .chipsets: section");
}

Test(parser, links_before_chipsets_throws) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".links:\n");
    bool thrown = false;
    try { (void)parser.parse(iss); } catch (const ParseError &) { thrown = true; }
    cr_assert(thrown, "Expected ParseError when .links: appears before .chipsets:");
}

Test(parser, content_outside_section_throws) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss("input a\n.chipsets:\n");
    bool thrown = false;
    try { (void)parser.parse(iss); } catch (const ParseError &) { thrown = true; }
    cr_assert(thrown, "Expected ParseError for content outside any section");
}

Test(parser, clock_registered) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".chipsets:\nclock ck1\n.links:\n");
    Circuit circuit = parser.parse(iss);
    cr_assert(circuit.hasComponent("ck1"), "Clock component should be registered");
}

Test(parser, pin_zero_throws) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".chipsets:\ninput a\noutput b\n.links:\na:0 b:1\n");
    bool thrown = false;
    try { (void)parser.parse(iss); } catch (const ParseError &) { thrown = true; }
    cr_assert(thrown, "Expected ParseError when pin number is 0");
}

Test(parser, extra_chars_chipset_line_throws) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".chipsets:\ninput a extra\n");
    bool thrown = false;
    try { (void)parser.parse(iss); } catch (const ParseError &) { thrown = true; }
    cr_assert(thrown, "Expected ParseError on extra tokens at end of chipset line");
}

Test(parser, extra_chars_link_line_throws) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".chipsets:\ninput a\noutput b\n.links:\na:1 b:1 extra\n");
    bool thrown = false;
    try { (void)parser.parse(iss); } catch (const ParseError &) { thrown = true; }
    cr_assert(thrown, "Expected ParseError on extra tokens at end of link line");
}

Test(parser, extra_content_after_section_header_ignored) {
    TestFactory factory;
    Parser parser(factory);
    std::istringstream iss(".chipsets: extra stuff\ninput a\n.links: more extra\n");
    Circuit circuit = parser.parse(iss);
    cr_assert(circuit.hasComponent("a"), "Extra content after section header should be ignored");
}

Test(parser, parse_from_file_success) {
    TestFactory factory;
    Parser parser(factory);
    const char *tmpPath = "/tmp/test_tekspice_parser.nts";
    {
        std::ofstream f(tmpPath);
        f << ".chipsets:\ninput a\n.links:\n";
    }
    Circuit circuit = parser.parse(std::string(tmpPath));
    std::remove(tmpPath);
    cr_assert(circuit.hasComponent("a"), "Component from file should be parsed correctly");
}

Test(output, simulate_no_crash) {
    Output out("out");
    out.simulate(1);
    cr_assert(true, "Output simulate() should not crash");
}

Test(c4512, simulate_no_crash) {
    C4512 chip("chip");
    chip.simulate(1);
    cr_assert(true, "C4512 simulate() should not crash");
}

Test(c4512, input_pin_direct_read) {
    C4512 chip("chip");
    auto *src = wirePin(chip, 1); src->value = True;
    cr_assert_eq(chip.compute(1), True, "compute(1) should return the linked value");
}

Test(c4512, undefined_address_gives_undefined) {
    C4512 chip("chip");
    wirePin(chip, 10)->value = False;
    wirePin(chip, 15)->value = True;
    wirePin(chip, 11)->value = Undefined;
    wirePin(chip, 12)->value = False;
    wirePin(chip, 13)->value = False;
    cr_assert_eq(chip.compute(14), Undefined, "Undefined address pin must give Undefined output");
}

Test(c4512, invalid_pin_throws) {
    C4512 chip("chip");
    bool thrown = false;
    try { chip.compute(17); } catch (const NtsException &) { thrown = true; }
    cr_assert(thrown, "Invalid pin must throw NtsException");
}

Test(c4512, selects_channel_1) {
    C4512 chip("chip");
    wirePin(chip, 10)->value = False;
    wirePin(chip, 15)->value = True;
    wirePin(chip, 11)->value = True;
    wirePin(chip, 12)->value = False;
    wirePin(chip, 13)->value = False;
    wirePin(chip,  1)->value = False;
    wirePin(chip,  2)->value = True;
    cr_assert_eq(chip.compute(14), True, "Channel 1 (pin 2) must be selected when A=1,B=0,C=0");
}

Test(c2716, simulate_no_crash) {
    C2716 chip("chip");
    chip.simulate(1);
    cr_assert(true, "C2716 simulate() should not crash");
}

Test(c2716, power_pins_throw) {
    C2716 chip("chip");
    bool t12 = false, t21 = false, t24 = false;
    try { chip.compute(12); } catch (const NtsException &) { t12 = true; }
    try { chip.compute(21); } catch (const NtsException &) { t21 = true; }
    try { chip.compute(24); } catch (const NtsException &) { t24 = true; }
    cr_assert(t12, "Pin 12 must throw");
    cr_assert(t21, "Pin 21 must throw");
    cr_assert(t24, "Pin 24 must throw");
}

Test(c2716, input_pin_returns_linked_value) {
    C2716 chip("chip");
    wirePin(chip, 8)->value = True;
    cr_assert_eq(chip.compute(8), True, "Input pin 8 should return the linked value");
}

Test(c2716, output_undefined_without_enable) {
    C2716 chip("chip");
    wirePin(chip, 18)->value = False;
    wirePin(chip, 20)->value = True;
    for (auto p : {8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u, 19u})
        wirePin(chip, p)->value = False;
    cr_assert_eq(chip.compute(9), Undefined, "Output must be Undefined when CE is not True");
}

Test(c2716, output_reads_data_all_pins) {
    C2716 chip("chip");
    wirePin(chip, 18)->value = True;
    wirePin(chip, 20)->value = True;
    for (auto p : {8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u, 19u})
        wirePin(chip, p)->value = False;
    for (auto p : {9u, 10u, 11u, 13u, 14u, 15u, 16u, 17u}) {
        Tristate r = chip.compute(p);
        cr_assert(r == True || r == False, "Output pin must return True or False when enabled");
    }
}

Test(c2716, output_undefined_with_undefined_address) {
    C2716 chip("chip");
    wirePin(chip, 18)->value = True;
    wirePin(chip, 20)->value = True;
    wirePin(chip,  8)->value = Undefined;
    for (auto p : {7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u, 19u})
        wirePin(chip, p)->value = False;
    cr_assert_eq(chip.compute(9), Undefined, "Undefined address pin must give Undefined output");
}

Test(c2716, invalid_pin_throws) {
    C2716 chip("chip");
    bool thrown = false;
    try { chip.compute(25); } catch (const NtsException &) { thrown = true; }
    cr_assert(thrown, "Invalid pin must throw NtsException");
}

Test(c2716, output_undefined_without_oe) {
    C2716 chip("chip");
    wirePin(chip, 18)->value = True;
    wirePin(chip, 20)->value = False;
    for (auto p : {8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u, 19u})
        wirePin(chip, p)->value = False;
    cr_assert_eq(chip.compute(9), Undefined, "Output must be Undefined when OE is not True");
}

Test(c2716, output_reads_nonzero_address) {
    C2716 chip("chip");
    wirePin(chip, 18)->value = True;
    wirePin(chip, 20)->value = True;
    wirePin(chip,  8)->value = True;
    for (auto p : {7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u, 19u})
        wirePin(chip, p)->value = False;
    Tristate r = chip.compute(9);
    cr_assert(r == True || r == False, "Output with address=1 must return True or False");
}

Test(c2716, loads_rom_file_padding) {
    {
        std::ofstream f("./rom.bin", std::ios::binary);
        uint8_t byte = 0xAA;
        f.write(reinterpret_cast<char *>(&byte), 1);
    }
    C2716 chip("rom_load_test");
    std::remove("./rom.bin");
    wirePin(chip, 18)->value = True;
    wirePin(chip, 20)->value = True;
    for (auto p : {8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 23u, 22u, 19u})
        wirePin(chip, p)->value = False;
    Tristate r9  = chip.compute(9);
    Tristate r10 = chip.compute(10);
    cr_assert(r9  == True || r9  == False);
    cr_assert(r10 == True || r10 == False);
}

Test(or_gate, input_pin_returns_linked_value) {
  OrGate g("g");
  TestableComponent src;
  src.value = True;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(1), True, "compute(1) should return linked value");
}

Test(xor_gate, input_pin_returns_linked_value) {
  XorGate g("g");
  TestableComponent src;
  src.value = False;
  g.setLink(2, src, 1);
  cr_assert_eq(g.compute(2), False, "compute(2) should return linked value");
}

Test(nor_gate, input_pin_returns_linked_value) {
  NorGate g("g");
  TestableComponent src;
  src.value = True;
  g.setLink(1, src, 1);
  cr_assert_eq(g.compute(1), True, "compute(1) should return linked value");
}

Test(acomponent, computing_flag_cycle_returns_undefined) {
  AndGate a("a"), b("b");
  a.setLink(1, b, 3);
  b.setLink(1, a, 3);
  Tristate result = a.compute(3);
  cr_assert_eq(result, Undefined,
               "Circular compute should return Undefined via _computing guard");
}

Test(circuit, add_null_component_throws) {
  Circuit c;
  bool thrown = false;
  try {
    c.addComponent("foo", nullptr);
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "addComponent(nullptr) should throw ParseError");
}

Test(circuit, const_get_unknown_throws) {
  Circuit c;
  c.addComponent("foo", std::make_unique<TestableComponent>());
  const Circuit &cc = c;
  bool thrown = false;
  try {
    (void)cc.getComponent("nonexistent");
  } catch (const ParseError &) {
    thrown = true;
  }
  cr_assert(thrown, "const getComponent for unknown should throw ParseError");
}

Test(circuit, const_get_known_succeeds) {
  Circuit c;
  c.addComponent("foo", std::make_unique<TestableComponent>());
  const Circuit &cc = c;
  bool noThrow = true;
  try {
    (void)cc.getComponent("foo");
  } catch (...) {
    noThrow = false;
  }
  cr_assert(noThrow, "const getComponent for existing component should not throw");
}

Test(circuit, compute_all_outputs_no_crash) {
  Circuit c;
  auto out = std::make_unique<TestableComponent>();
  out->value = True;
  c.addComponent("out1", std::move(out));
  c.addOutputName("out1");
  bool noThrow = true;
  try {
    c.computeAllOutputs();
  } catch (...) {
    noThrow = false;
  }
  cr_assert(noThrow, "computeAllOutputs should not throw");
}

Test(circuit, display_undefined_value, .init = cr_redirect_stdout) {
  Circuit c;
  auto in = std::make_unique<TestableComponent>();
  c.addComponent("in_u", std::move(in));
  c.addInputName("in_u");
  c.display();
  cr_assert_stdout_eq_str("tick: 0\n"
                          "input(s):\n"
                          "  in_u: U\n"
                          "output(s):\n");
}

Test(circuit, set_input_not_registered_throws) {
  Circuit c;
  c.addComponent("out1", std::make_unique<TestableComponent>());
  bool thrown = false;
  try {
    c.setInputValue("out1", "1");
  } catch (const NtsException &) {
    thrown = true;
  }
  cr_assert(thrown,
            "setInputValue on component not registered as input/clock should throw");
}

Test(lexer, digit_alpha_mixed_token_is_identifier) {
  Lexer lexer("42abc");
  Token t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::IDENTIFIER,
               "Token starting with digit but containing alpha should be IDENTIFIER");
  cr_assert_str_eq(t.value.c_str(), "42abc");
}

Test(lexer, digit_underscore_mixed_token_is_identifier) {
  Lexer lexer("1_foo");
  Token t = lexer.nextToken();
  cr_assert_eq(t.type, TokenType::IDENTIFIER,
               "Token starting with digit but containing underscore should be IDENTIFIER");
  cr_assert_str_eq(t.value.c_str(), "1_foo");
}
