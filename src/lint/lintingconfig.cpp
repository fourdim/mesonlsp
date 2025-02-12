#include "lintingconfig.hpp"

#include <filesystem>
#include <toml++/toml.hpp>

void MesonLintConfig::load(const std::filesystem::path &path) {
  const auto &configFile = path / ".mesonlint.toml";
  if (!std::filesystem::exists(configFile)) {
    return;
  }
  auto result = toml::parse_file(configFile.generic_string());
  if (result.contains("formatting") &&
      result.get("formatting")->type() == toml::v3::node_type::table) {
    const auto *formatting = result["formatting"].as_table();
    if (formatting->contains("max_line_len") &&
        formatting->get("max_line_len")->type() ==
            toml::v3::node_type::integer) {
      this->formatting.max_line_len =
          (int)formatting->get("max_line_len")->as_integer()->get();
    }
    if (formatting->contains("mode") &&
        formatting->get("mode")->type() == toml::v3::node_type::string) {
      this->formatting.mode =
          formatting->get("mode")->as_string()->get() == "tracked"
              ? FileFinderMode::TRACKED
              : FileFinderMode::ALL;
    }
    if (formatting->contains("indent_by") &&
        formatting->get("indent_by")->type() == toml::v3::node_type::string) {
      this->formatting.indent_by =
          formatting->get("indent_by")->as_string()->get();
    }
    if (formatting->contains("space_array") &&
        formatting->get("space_array")->type() ==
            toml::v3::node_type::boolean) {
      this->formatting.space_array =
          formatting->get("space_array")->as_boolean()->get();
    }
    if (formatting->contains("kwargs_force_multiline") &&
        formatting->get("kwargs_force_multiline")->type() ==
            toml::v3::node_type::boolean) {
      this->formatting.kwargs_force_multiline =
          formatting->get("kwargs_force_multiline")->as_boolean()->get();
    }
    if (formatting->contains("wide_colon") &&
        formatting->get("wide_colon")->type() == toml::v3::node_type::boolean) {
      this->formatting.wide_colon =
          formatting->get("wide_colon")->as_boolean()->get();
    }
    if (formatting->contains("no_single_comma_function") &&
        formatting->get("no_single_comma_function")->type() ==
            toml::v3::node_type::boolean) {
      this->formatting.no_single_comma_function =
          formatting->get("no_single_comma_function")->as_boolean()->get();
    }
    if (formatting->contains("indent_style") &&
        formatting->get("indent_style")->type() ==
            toml::v3::node_type::string) {
      this->formatting.indent_style =
          formatting->get("indent_style")->as_string()->get();
    }
    if (formatting->contains("indent_size") &&
        formatting->get("indent_size")->type() ==
            toml::v3::node_type::integer) {
      this->formatting.indent_size =
          (int)formatting->get("indent_size")->as_integer()->get();
    }
    if (formatting->contains("insert_final_newline") &&
        formatting->get("insert_final_newline")->type() ==
            toml::v3::node_type::boolean) {
      this->formatting.insert_final_newline =
          formatting->get("insert_final_newline")->as_boolean()->get();
    }
    if (formatting->contains("sort_files") &&
        formatting->get("sort_files")->type() == toml::v3::node_type::boolean) {
      this->formatting.sort_files =
          formatting->get("sort_files")->as_boolean()->get();
    }
    if (formatting->contains("group_arg_value") &&
        formatting->get("group_arg_value")->type() ==
            toml::v3::node_type::boolean) {
      this->formatting.group_arg_value =
          formatting->get("group_arg_value")->as_boolean()->get();
    }
    if (formatting->contains("simplify_string_literals") &&
        formatting->get("simplify_string_literals")->type() ==
            toml::v3::node_type::boolean) {
      this->formatting.simplify_string_literals =
          formatting->get("simplify_string_literals")->as_boolean()->get();
    }
    if (formatting->contains("indent_before_comments") &&
        formatting->get("indent_before_comments")->type() ==
            toml::v3::node_type::string) {
      this->formatting.indent_before_comments =
          formatting->get("indent_before_comments")->as_string()->get();
    }
    if (formatting->contains("end_of_line") &&
        formatting->get("end_of_line")->type() == toml::v3::node_type::string) {
      this->formatting.end_of_line =
          formatting->get("end_of_line")->as_string()->get();
    }
  }
  if (result.contains("linting") &&
      result.get("linting")->type() == toml::v3::node_type::table) {
    const auto *linting_table = result.get("linting")->as_table();
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define DESERIALIZE_ANALYSIS_OPTION(key)                                       \
  if (linting_table->contains(TOSTRING(key)) &&                                \
      linting_table->get(TOSTRING(key))->type() ==                             \
          toml::v3::node_type::boolean) {                                      \
    this->linting.options.key =                                                \
        linting_table->get(TOSTRING(key))->as_boolean()->get();                \
  }
    DESERIALIZE_ANALYSIS_OPTION(disableNameLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableAllIdLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableCompilerIdLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableCompilerArgumentIdLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableLinkerIdLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableCpuFamilyLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableOsFamilyLinting)
    DESERIALIZE_ANALYSIS_OPTION(disableUnusedVariableCheck)
    DESERIALIZE_ANALYSIS_OPTION(disableArgTypeChecking)
    DESERIALIZE_ANALYSIS_OPTION(disableIterationVariableShadowingLint)
    DESERIALIZE_ANALYSIS_OPTION(enableIterationVariableLint)
  }
}
