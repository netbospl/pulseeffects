/*
 *  Copyright © 2017-2020 Wellington Wallace
 *
 *  This file is part of PulseEffects.
 *
 *  PulseEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PulseEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with PulseEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "crystalizer_preset.hpp"

CrystalizerPreset::CrystalizerPreset()
    : output_settings(Gio::Settings::create("com.github.wwmm.pulseeffects.crystalizer",
                                            "/com/github/wwmm/pulseeffects/sinkinputs/crystalizer/")) {}

void CrystalizerPreset::save(boost::property_tree::ptree& root,
                             const std::string& section,
                             const Glib::RefPtr<Gio::Settings>& settings) {
  root.put(section + ".crystalizer.state", settings->get_boolean("state"));

  root.put(section + ".crystalizer.aggressive", settings->get_boolean("aggressive"));

  root.put(section + ".crystalizer.input-gain", settings->get_double("input-gain"));

  root.put(section + ".crystalizer.output-gain", settings->get_double("output-gain"));

  for (int n = 0; n < 13; n++) {
    root.put(section + ".crystalizer.band" + std::to_string(n) + ".intensity",
             settings->get_double("intensity-band" + std::to_string(n)));

    root.put(section + ".crystalizer.band" + std::to_string(n) + ".mute",
             settings->get_boolean("mute-band" + std::to_string(n)));

    root.put(section + ".crystalizer.band" + std::to_string(n) + ".bypass",
             settings->get_boolean("bypass-band" + std::to_string(n)));
  }
}

void CrystalizerPreset::load(const boost::property_tree::ptree& root,
                             const std::string& section,
                             const Glib::RefPtr<Gio::Settings>& settings) {
  update_key<bool>(root, settings, "state", section + ".crystalizer.state");

  update_key<bool>(root, settings, "aggressive", section + ".crystalizer.aggressive");

  update_key<double>(root, settings, "input-gain", section + ".crystalizer.input-gain");

  update_key<double>(root, settings, "output-gain", section + ".crystalizer.output-gain");

  for (int n = 0; n < 13; n++) {
    update_key<double>(root, settings, "intensity-band" + std::to_string(n),
                       section + ".crystalizer.band" + std::to_string(n) + ".intensity");

    update_key<bool>(root, settings, "mute-band" + std::to_string(n),
                     section + ".crystalizer.band" + std::to_string(n) + ".mute");

    update_key<bool>(root, settings, "bypass-band" + std::to_string(n),
                     section + ".crystalizer.band" + std::to_string(n) + ".bypass");
  }
}

void CrystalizerPreset::write(PresetType preset_type, boost::property_tree::ptree& root) {
  if (preset_type == PresetType::output) {
    save(root, "output", output_settings);
  }
}

void CrystalizerPreset::read(PresetType preset_type, const boost::property_tree::ptree& root) {
  if (preset_type == PresetType::output) {
    load(root, "output", output_settings);
  }
}
