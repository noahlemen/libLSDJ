/*

 This file is a part of liblsdj, a C library for managing everything
 that has to do with LSDJ, software for writing music (chiptune) with
 your gameboy. For more information, see:

 * https://github.com/stijnfrishert/liblsdj
 * http://www.littlesounddj.com

 --------------------------------------------------------------------------------

 MIT License

 Copyright (c) 2018 - 2020 Stijn Frishert

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 */

#ifndef LSDJ_EXPORTER_HPP
#define LSDJ_EXPORTER_HPP

#include <filesystem>
#include <string>
#include <vector>

#include <lsdj/error.h>
#include <lsdj/project.h>
#include <lsdj/sav.h>

namespace lsdj {
class Exporter {
public:
  enum class VersionStyle { NONE, HEX, DECIMAL };

public:
  int export_(const std::filesystem::path &path);
  int print(const std::filesystem::path &path);

public:
  // The version exporting style
  VersionStyle versionStyle = VersionStyle::HEX;

  bool underscore = false;
  bool putInFolder = false;
  bool verbose = false;
  bool skipWorkingMemory = false;

  std::vector<int> indices;
  std::vector<std::string> names;
  std::string output;

private:
  int exportFolder(const std::filesystem::path &path);
  int exportSav(const std::filesystem::path &path);
  int printFolder(const std::filesystem::path &path);
  int printSav(const std::filesystem::path &path);
  bool shouldExportWorkingMemory();

  // Export an actual project
  lsdj_error_t exportProject(const lsdj_project_t *project,
                             std::filesystem::path folder, bool workingMemory);

  // Converts a project version to a string representation using the current
  // VersionStyle
  std::string convertVersionToString(uint8_t version, bool prefixDot,
                                     bool prefixWhitespace) const;

  // Print the working memory song line
  void printWorkingMemorySong(const lsdj_sav_t *sav);

  // Print a sav project line
  void printProject(const lsdj_sav_t *sav, std::uint8_t index);

  std::string constructName(const lsdj_project_t *project);
};
} // namespace lsdj

#endif
