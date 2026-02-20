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
  createComponent(const std::string &) const override {
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
