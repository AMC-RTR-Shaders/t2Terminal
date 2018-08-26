import bpy
cameras = {}
scene = bpy.context.scene
frame = scene.frame_current - 1

data = bpy.data.cameras.new('Camera')
data.lens = 35.0
data.shift_x = 0.0
data.shift_y = 0.0
data.dof_distance = 0.0
data.clip_start = 0.10000000149011612
data.clip_end = 100.0
data.draw_size = 0.5
obj = bpy.data.objects.new('Camera', data)
obj.hide_render = False
scene.objects.link(obj)
cameras['Camera'] = obj

# new frame
scene.frame_set(1 + frame)
obj = cameras['Camera']
obj.location = -2.9666316509246826, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(2 + frame)
obj = cameras['Camera']
obj.location = -2.9211671352386475, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(3 + frame)
obj = cameras['Camera']
obj.location = -2.8791885375976562, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(4 + frame)
obj = cameras['Camera']
obj.location = -2.839188575744629, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(5 + frame)
obj = cameras['Camera']
obj.location = -2.7991886138916016, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(6 + frame)
obj = cameras['Camera']
obj.location = -2.759188175201416, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(7 + frame)
obj = cameras['Camera']
obj.location = -2.7191884517669678, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(8 + frame)
obj = cameras['Camera']
obj.location = -2.6791882514953613, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(9 + frame)
obj = cameras['Camera']
obj.location = -2.639188289642334, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(10 + frame)
obj = cameras['Camera']
obj.location = -2.5991883277893066, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(11 + frame)
obj = cameras['Camera']
obj.location = -2.5591883659362793, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(12 + frame)
obj = cameras['Camera']
obj.location = -2.519188404083252, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(13 + frame)
obj = cameras['Camera']
obj.location = -2.4791884422302246, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(14 + frame)
obj = cameras['Camera']
obj.location = -2.4391884803771973, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(15 + frame)
obj = cameras['Camera']
obj.location = -2.39918851852417, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(16 + frame)
obj = cameras['Camera']
obj.location = -2.3591885566711426, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(17 + frame)
obj = cameras['Camera']
obj.location = -2.3191885948181152, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(18 + frame)
obj = cameras['Camera']
obj.location = -2.279188632965088, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(19 + frame)
obj = cameras['Camera']
obj.location = -2.2391884326934814, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(20 + frame)
obj = cameras['Camera']
obj.location = -2.199188470840454, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(21 + frame)
obj = cameras['Camera']
obj.location = -2.159188747406006, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(22 + frame)
obj = cameras['Camera']
obj.location = -2.1191883087158203, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(23 + frame)
obj = cameras['Camera']
obj.location = -2.079188346862793, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(24 + frame)
obj = cameras['Camera']
obj.location = -2.0391886234283447, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(25 + frame)
obj = cameras['Camera']
obj.location = -1.9991885423660278, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(26 + frame)
obj = cameras['Camera']
obj.location = -1.9591885805130005, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(27 + frame)
obj = cameras['Camera']
obj.location = -1.9191886186599731, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(28 + frame)
obj = cameras['Camera']
obj.location = -1.879188895225525, -3.1495983600616455, 1.3526740074157715
obj.scale = 1.000000238418579, 1.000000238418579, 1.000000238418579
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(29 + frame)
obj = cameras['Camera']
obj.location = -1.8391886949539185, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(30 + frame)
obj = cameras['Camera']
obj.location = -1.7991886138916016, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(31 + frame)
obj = cameras['Camera']
obj.location = -1.7591886520385742, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(32 + frame)
obj = cameras['Camera']
obj.location = -1.7191885709762573, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(33 + frame)
obj = cameras['Camera']
obj.location = -1.679188847541809, -3.1495983600616455, 1.3526740074157715
obj.scale = 1.000000238418579, 1.000000238418579, 1.000000238418579
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(34 + frame)
obj = cameras['Camera']
obj.location = -1.6391888856887817, -3.1495983600616455, 1.3526740074157715
obj.scale = 1.000000238418579, 1.000000238418579, 1.000000238418579
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(35 + frame)
obj = cameras['Camera']
obj.location = -1.5991889238357544, -3.1495983600616455, 1.3526740074157715
obj.scale = 1.000000238418579, 1.000000238418579, 1.000000238418579
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(36 + frame)
obj = cameras['Camera']
obj.location = -1.5591888427734375, -3.1495983600616455, 1.3526740074157715
obj.scale = 1.000000238418579, 1.000000238418579, 1.000000238418579
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(37 + frame)
obj = cameras['Camera']
obj.location = -1.5191888809204102, -3.1495983600616455, 1.3526740074157715
obj.scale = 1.000000238418579, 1.000000238418579, 1.000000238418579
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(38 + frame)
obj = cameras['Camera']
obj.location = -1.4791885614395142, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(39 + frame)
obj = cameras['Camera']
obj.location = -1.4391885995864868, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(40 + frame)
obj = cameras['Camera']
obj.location = -1.39918851852417, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(41 + frame)
obj = cameras['Camera']
obj.location = -1.3591885566711426, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(42 + frame)
obj = cameras['Camera']
obj.location = -1.3191885948181152, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(43 + frame)
obj = cameras['Camera']
obj.location = -1.2791885137557983, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(44 + frame)
obj = cameras['Camera']
obj.location = -1.2391886711120605, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(45 + frame)
obj = cameras['Camera']
obj.location = -1.1991887092590332, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(46 + frame)
obj = cameras['Camera']
obj.location = -1.1591885089874268, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(47 + frame)
obj = cameras['Camera']
obj.location = -1.1191885471343994, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(48 + frame)
obj = cameras['Camera']
obj.location = -1.0791887044906616, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(49 + frame)
obj = cameras['Camera']
obj.location = -1.0391886234283447, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(50 + frame)
obj = cameras['Camera']
obj.location = -0.9991886615753174, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(51 + frame)
obj = cameras['Camera']
obj.location = -0.95918869972229, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(52 + frame)
obj = cameras['Camera']
obj.location = -0.9191887378692627, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(53 + frame)
obj = cameras['Camera']
obj.location = -0.8791887760162354, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(54 + frame)
obj = cameras['Camera']
obj.location = -0.8391885757446289, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(55 + frame)
obj = cameras['Camera']
obj.location = -0.7991886138916016, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(56 + frame)
obj = cameras['Camera']
obj.location = -0.7591886520385742, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(57 + frame)
obj = cameras['Camera']
obj.location = -0.719188928604126, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(58 + frame)
obj = cameras['Camera']
obj.location = -0.6791889667510986, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(59 + frame)
obj = cameras['Camera']
obj.location = -0.6391887664794922, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(60 + frame)
obj = cameras['Camera']
obj.location = -0.5991885662078857, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(61 + frame)
obj = cameras['Camera']
obj.location = -0.5591886043548584, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(62 + frame)
obj = cameras['Camera']
obj.location = -0.5191888809204102, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(63 + frame)
obj = cameras['Camera']
obj.location = -0.4791886806488037, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(64 + frame)
obj = cameras['Camera']
obj.location = -0.43918871879577637, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(65 + frame)
obj = cameras['Camera']
obj.location = -0.399188756942749, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(66 + frame)
obj = cameras['Camera']
obj.location = -0.3591885566711426, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(67 + frame)
obj = cameras['Camera']
obj.location = -0.31918859481811523, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(68 + frame)
obj = cameras['Camera']
obj.location = -0.2791886329650879, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(69 + frame)
obj = cameras['Camera']
obj.location = -0.23918867111206055, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(70 + frame)
obj = cameras['Camera']
obj.location = -0.1991889476776123, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(71 + frame)
obj = cameras['Camera']
obj.location = -0.15918874740600586, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(72 + frame)
obj = cameras['Camera']
obj.location = -0.11918878555297852, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(73 + frame)
obj = cameras['Camera']
obj.location = -0.07918882369995117, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(74 + frame)
obj = cameras['Camera']
obj.location = -0.03918886184692383, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(75 + frame)
obj = cameras['Camera']
obj.location = 0.0008111000061035156, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(76 + frame)
obj = cameras['Camera']
obj.location = 0.04081130027770996, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(77 + frame)
obj = cameras['Camera']
obj.location = 0.0808110237121582, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(78 + frame)
obj = cameras['Camera']
obj.location = 0.12081122398376465, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(79 + frame)
obj = cameras['Camera']
obj.location = 0.1608114242553711, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(80 + frame)
obj = cameras['Camera']
obj.location = 0.20081138610839844, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(81 + frame)
obj = cameras['Camera']
obj.location = 0.24081134796142578, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(82 + frame)
obj = cameras['Camera']
obj.location = 0.280811071395874, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(83 + frame)
obj = cameras['Camera']
obj.location = 0.32081079483032227, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(84 + frame)
obj = cameras['Camera']
obj.location = 0.3608112335205078, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(85 + frame)
obj = cameras['Camera']
obj.location = 0.40081119537353516, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(86 + frame)
obj = cameras['Camera']
obj.location = 0.4408113956451416, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(87 + frame)
obj = cameras['Camera']
obj.location = 0.48081111907958984, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(88 + frame)
obj = cameras['Camera']
obj.location = 0.5208113193511963, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(89 + frame)
obj = cameras['Camera']
obj.location = 0.5608112812042236, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(90 + frame)
obj = cameras['Camera']
obj.location = 0.600811243057251, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(91 + frame)
obj = cameras['Camera']
obj.location = 0.6408112049102783, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(92 + frame)
obj = cameras['Camera']
obj.location = 0.6808114051818848, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(93 + frame)
obj = cameras['Camera']
obj.location = 0.7208113670349121, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(94 + frame)
obj = cameras['Camera']
obj.location = 0.7608115673065186, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(95 + frame)
obj = cameras['Camera']
obj.location = 0.8008112907409668, -3.1495981216430664, 1.3526737689971924
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(96 + frame)
obj = cameras['Camera']
obj.location = 0.8408112525939941, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(97 + frame)
obj = cameras['Camera']
obj.location = 0.8808114528656006, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(98 + frame)
obj = cameras['Camera']
obj.location = 0.9227902889251709, -3.149597406387329, 1.3526737689971924
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(99 + frame)
obj = cameras['Camera']
obj.location = 0.968254566192627, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(100 + frame)
obj = cameras['Camera']
obj.location = 1.0008113384246826, -3.149597644805908, 1.3526737689971924
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 1.1093189716339111, -3.556264933915036e-18, -1.5547796487808228
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# markers
