#include "../includes/event.hpp"
#include "../includes/engine.hpp"

#include "imconfig.h"
#include "imgui-SFML.h"
#include "imgui-SFML_export.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <algorithm>

void    GUIColors(void);
void    object_window(Engine &engine);