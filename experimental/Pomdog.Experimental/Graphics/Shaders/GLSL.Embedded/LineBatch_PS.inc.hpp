// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

char const* Builtin_GLSL_LineBatch_PS =
"#version 330\n"
"in VertexData{\n"
"vec4 DestinationColor;}In;\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor=In.DestinationColor;}\n";
