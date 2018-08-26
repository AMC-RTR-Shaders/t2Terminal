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
obj.location = -0.39716148376464844, -3.776535987854004, -4.767633438110352
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999998807907104
obj.rotation_euler = 2.4293875694274902, -0.0, -0.08313758671283722
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(2 + frame)
obj = cameras['Camera']
obj.location = -0.7740669250488281, -3.7765393257141113, -4.714576244354248
obj.scale = 0.9999998807907104, 1.0, 0.9999999403953552
obj.rotation_euler = 2.4204187393188477, -0.0, -0.15724898874759674
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(3 + frame)
obj = cameras['Camera']
obj.location = -1.1479644775390625, -3.776543140411377, -4.638901710510254
obj.scale = 0.9999998807907104, 0.9999998211860657, 1.0
obj.rotation_euler = 2.4068779945373535, 7.450580152834618e-09, -0.22909219563007355
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(4 + frame)
obj = cameras['Camera']
obj.location = -1.5148639678955078, -3.776548147201538, -4.541505336761475
obj.scale = 0.9999999403953552, 0.9999998807907104, 0.9999998807907104
obj.rotation_euler = 2.3891165256500244, 1.4901161193847656e-08, -0.29733341932296753
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(5 + frame)
obj = cameras['Camera']
obj.location = -1.8810157775878906, -3.776554584503174, -4.429255485534668
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999998807907104
obj.rotation_euler = 2.367807626724243, -1.4901161193847656e-08, -0.3627086281776428
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(6 + frame)
obj = cameras['Camera']
obj.location = -2.249960422515869, -3.7765612602233887, -4.305401802062988
obj.scale = 0.9999999403953552, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 2.343337059020996, 1.4901161193847656e-08, -0.42545968294143677
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(7 + frame)
obj = cameras['Camera']
obj.location = -2.6238179206848145, -3.7765676975250244, -4.171503067016602
obj.scale = 0.9999999403953552, 1.0, 1.0
obj.rotation_euler = 2.315993309020996, -0.0, -0.48560523986816406
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(8 + frame)
obj = cameras['Camera']
obj.location = -3.005009651184082, -3.776576519012451, -4.027688026428223
obj.scale = 1.0, 1.0, 0.9999998807907104
obj.rotation_euler = 2.2859394550323486, 1.4901161193847656e-08, -0.5432372093200684
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(9 + frame)
obj = cameras['Camera']
obj.location = -3.3917179107666016, -3.776583671569824, -3.8692197799682617
obj.scale = 1.0, 1.0, 1.0
obj.rotation_euler = 2.2530713081359863, 1.4901161193847656e-08, -0.5978752970695496
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(10 + frame)
obj = cameras['Camera']
obj.location = -3.7696914672851562, -3.7765939235687256, -3.6841859817504883
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 2.217144012451172, -1.4901160305669237e-08, -0.6476236581802368
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(11 + frame)
obj = cameras['Camera']
obj.location = -4.0963640213012695, -3.7766077518463135, -3.452298164367676
obj.scale = 0.9999999403953552, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 2.178264856338501, -0.0, -0.687809944152832
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(12 + frame)
obj = cameras['Camera']
obj.location = -4.311491012573242, -3.7766220569610596, -3.1569042205810547
obj.scale = 0.9999999403953552, 1.0, 0.9999997615814209
obj.rotation_euler = 2.1372687816619873, -1.4901161193847656e-08, -0.712907075881958
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(13 + frame)
obj = cameras['Camera']
obj.location = -4.453592777252197, -3.7766408920288086, -2.827176094055176
obj.scale = 0.9999997615814209, 0.9999997615814209, 0.9999998807907104
obj.rotation_euler = 2.0949063301086426, 1.4901161193847656e-08, -0.7289091944694519
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(14 + frame)
obj = cameras['Camera']
obj.location = -4.647607326507568, -3.776657819747925, -2.5154972076416016
obj.scale = 0.9999997019767761, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 2.051478862762451, 1.4901161193847656e-08, -0.7500423192977905
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(15 + frame)
obj = cameras['Camera']
obj.location = -4.9247026443481445, -3.776671886444092, -2.2242116928100586
obj.scale = 1.0, 0.9999999403953552, 0.9999998211860657
obj.rotation_euler = 2.006786584854126, -0.0, -0.7788446545600891
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(16 + frame)
obj = cameras['Camera']
obj.location = -5.2192816734313965, -3.776689052581787, -1.9223289489746094
obj.scale = 0.9999999403953552, 1.0, 1.0
obj.rotation_euler = 1.9605406522750854, -1.4901159417490817e-08, -0.8077672123908997
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(17 + frame)
obj = cameras['Camera']
obj.location = -5.484025001525879, -3.776707887649536, -1.597691535949707
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999998807907104
obj.rotation_euler = 1.9132115840911865, -0.0, -0.8323498368263245
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(18 + frame)
obj = cameras['Camera']
obj.location = -5.700321197509766, -3.776726245880127, -1.2529096603393555
obj.scale = 0.9999998807907104, 1.0, 0.9999998807907104
obj.rotation_euler = 1.8655107021331787, -1.4901160305669237e-08, -0.8514952659606934
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(19 + frame)
obj = cameras['Camera']
obj.location = -5.866665840148926, -3.7767443656921387, -0.8943109512329102
obj.scale = 0.9999998211860657, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 1.8178651332855225, 7.4505797087454084e-09, -0.8656712174415588
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(20 + frame)
obj = cameras['Camera']
obj.location = -5.990167617797852, -3.776763916015625, -0.5269289016723633
obj.scale = 1.0, 0.9999998211860657, 0.9999998211860657
obj.rotation_euler = 1.7703319787979126, -0.0, -0.875899076461792
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(21 + frame)
obj = cameras['Camera']
obj.location = -6.079750061035156, -3.776784658432007, -0.15319538116455078
obj.scale = 0.9999999403953552, 0.9999997615814209, 0.9999998807907104
obj.rotation_euler = 1.7227305173873901, -0.0, -0.8831633925437927
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(22 + frame)
obj = cameras['Camera']
obj.location = -6.140018939971924, -3.7768054008483887, 0.2242755889892578
obj.scale = 0.9999997019767761, 0.9999998211860657, 0.9999997019767761
obj.rotation_euler = 1.6750941276550293, -0.0, -0.8879788517951965
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(23 + frame)
obj = cameras['Camera']
obj.location = -6.172436714172363, -3.776824474334717, 0.6016225814819336
obj.scale = 0.9999999403953552, 1.0, 1.0
obj.rotation_euler = 1.6277108192443848, 1.8626449271863521e-09, -0.8905448317527771
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(24 + frame)
obj = cameras['Camera']
obj.location = -6.187229156494141, -3.776843309402466, 0.9825906753540039
obj.scale = 1.0, 1.0, 1.0000001192092896
obj.rotation_euler = 1.579933762550354, 4.6566123179658803e-10, -0.8917092680931091
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(25 + frame)
obj = cameras['Camera']
obj.location = -6.18411111831665, -3.7768661975860596, 1.366734504699707
obj.scale = 0.9999998211860657, 0.9999999403953552, 0.9999999403953552
obj.rotation_euler = 1.5317878723144531, -0.0, -0.8914615511894226
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(26 + frame)
obj = cameras['Camera']
obj.location = -6.15342378616333, -3.7768847942352295, 1.7448387145996094
obj.scale = 1.0000001192092896, 0.9999998807907104, 1.0000001192092896
obj.rotation_euler = 1.484313726425171, -3.725290298461914e-09, -0.8890348076820374
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(27 + frame)
obj = cameras['Camera']
obj.location = -6.100363731384277, -3.7769060134887695, 2.121746063232422
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 1.436805009841919, -0.0, -0.8848056793212891
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(28 + frame)
obj = cameras['Camera']
obj.location = -6.024690628051758, -3.776926040649414, 2.495645523071289
obj.scale = 0.9999998807907104, 1.0, 0.9999998807907104
obj.rotation_euler = 1.389390468597412, 7.450580152834618e-09, -0.8786985874176025
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(29 + frame)
obj = cameras['Camera']
obj.location = -5.927292346954346, -3.776946544647217, 2.862544059753418
obj.scale = 0.9999999403953552, 0.9999997615814209, 0.9999998211860657
obj.rotation_euler = 1.342484951019287, -7.450580596923828e-09, -0.8707042932510376
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(30 + frame)
obj = cameras['Camera']
obj.location = -5.815041542053223, -3.7769651412963867, 3.2286949157714844
obj.scale = 0.9999998211860657, 0.9999998211860657, 0.9999998211860657
obj.rotation_euler = 1.2954235076904297, 1.4901161193847656e-08, -0.8612992167472839
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(31 + frame)
obj = cameras['Camera']
obj.location = -5.69118595123291, -3.7769854068756104, 3.5976390838623047
obj.scale = 0.9999997019767761, 0.9999997615814209, 0.9999996423721313
obj.rotation_euler = 1.2479168176651, -0.0, -0.8506774306297302
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(32 + frame)
obj = cameras['Camera']
obj.location = -5.557288646697998, -3.7770044803619385, 3.971493721008301
obj.scale = 1.0, 0.9999998211860657, 1.0
obj.rotation_euler = 1.1998794078826904, -1.4901159417490817e-08, -0.8388981223106384
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(33 + frame)
obj = cameras['Camera']
obj.location = -5.413475513458252, -3.7770252227783203, 4.35269021987915
obj.scale = 1.0, 0.9999999403953552, 1.0
obj.rotation_euler = 1.1512012481689453, 1.4901161193847656e-08, -0.825892984867096
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(34 + frame)
obj = cameras['Camera']
obj.location = -5.2550048828125, -3.7770473957061768, 4.739397048950195
obj.scale = 0.9999998211860657, 0.9999998807907104, 0.9999997615814209
obj.rotation_euler = 1.1020969152450562, 1.4901162970204496e-08, -0.8111249804496765
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(35 + frame)
obj = cameras['Camera']
obj.location = -5.069972038269043, -3.7770674228668213, 5.117369651794434
obj.scale = 0.9999998211860657, 0.9999997615814209, 0.9999997615814209
obj.rotation_euler = 1.0537269115447998, 1.4901161193847656e-08, -0.7932814955711365
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(36 + frame)
obj = cameras['Camera']
obj.location = -4.838083267211914, -3.777083396911621, 5.444039344787598
obj.scale = 1.0, 0.9999998211860657, 1.0
obj.rotation_euler = 1.0094748735427856, 1.4901162970204496e-08, -0.7699700593948364
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(37 + frame)
obj = cameras['Camera']
obj.location = -4.542687892913818, -3.7770960330963135, 5.659167289733887
obj.scale = 0.9999999403953552, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 0.9740946888923645, -2.980232594040899e-08, -0.7386707067489624
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(38 + frame)
obj = cameras['Camera']
obj.location = -4.212962627410889, -3.7771036624908447, 5.801274299621582
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999998807907104
obj.rotation_euler = 0.9444782733917236, -0.0, -0.7014963030815125
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(39 + frame)
obj = cameras['Camera']
obj.location = -3.901285171508789, -3.7771148681640625, 5.9952898025512695
obj.scale = 0.9999997615814209, 0.9999999403953552, 1.0
obj.rotation_euler = 0.9106460809707642, -0.0, -0.664068877696991
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(40 + frame)
obj = cameras['Camera']
obj.location = -3.6099958419799805, -3.7771289348602295, 6.272380828857422
obj.scale = 0.9999998807907104, 0.9999998211860657, 0.9999998211860657
obj.rotation_euler = 0.8703116774559021, -0.0, -0.6269869208335876
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(41 + frame)
obj = cameras['Camera']
obj.location = -3.3081130981445312, -3.7771449089050293, 6.566959381103516
obj.scale = 1.0, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 0.8290955424308777, -0.0, -0.5863351821899414
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(42 + frame)
obj = cameras['Camera']
obj.location = -2.9834794998168945, -3.777158737182617, 6.831701278686523
obj.scale = 1.0000001192092896, 0.9999999403953552, 1.0000003576278687
obj.rotation_euler = 0.7910725474357605, -1.4901159417490817e-08, -0.5400308966636658
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(43 + frame)
obj = cameras['Camera']
obj.location = -2.6386966705322266, -3.7771713733673096, 7.047996997833252
obj.scale = 0.9999997019767761, 0.9999998211860657, 0.9999998211860657
obj.rotation_euler = 0.7579798102378845, -0.0, -0.4878752529621124
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(44 + frame)
obj = cameras['Camera']
obj.location = -2.2800979614257812, -3.777179718017578, 7.21434211730957
obj.scale = 1.0, 1.0, 1.0
obj.rotation_euler = 0.7301753759384155, -1.4901159417490817e-08, -0.4303921163082123
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(45 + frame)
obj = cameras['Camera']
obj.location = -1.9127159118652344, -3.7771859169006348, 7.3378448486328125
obj.scale = 1.000000238418579, 0.9999998211860657, 1.0000001192092896
obj.rotation_euler = 0.7073261141777039, -0.0, -0.3681853413581848
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(46 + frame)
obj = cameras['Camera']
obj.location = -1.5389823913574219, -3.7771904468536377, 7.427431583404541
obj.scale = 1.000000238418579, 0.9999998807907104, 1.0000001192092896
obj.rotation_euler = 0.6889550089836121, -1.4901161193847656e-08, -0.30169185996055603
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(47 + frame)
obj = cameras['Camera']
obj.location = -1.1615123748779297, -3.777193784713745, 7.487700939178467
obj.scale = 1.0000001192092896, 0.9999998807907104, 1.000000238418579
obj.rotation_euler = 0.6749793291091919, 7.4505797087454084e-09, -0.23162628710269928
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(48 + frame)
obj = cameras['Camera']
obj.location = -0.7841634750366211, -3.7771971225738525, 7.520115852355957
obj.scale = 0.9999998211860657, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 0.6655502319335938, -0.0, -0.15919364988803864
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(49 + frame)
obj = cameras['Camera']
obj.location = -0.40319252014160156, -3.777198314666748, 7.534907341003418
obj.scale = 0.9999997615814209, 0.9999999403953552, 0.9999997615814209
obj.rotation_euler = 0.6599960923194885, 3.725290298461914e-09, -0.08432185649871826
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(50 + frame)
obj = cameras['Camera']
obj.location = -0.019052505493164062, -3.777195930480957, 7.531790256500244
obj.scale = 1.0000001192092896, 1.0, 1.0
obj.rotation_euler = 0.6585205793380737, 2.3283064365386963e-10, -0.007859746925532818
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(51 + frame)
obj = cameras['Camera']
obj.location = 0.3590526580810547, -3.777195453643799, 7.5010986328125
obj.scale = 1.0, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 0.6619107127189636, -0.0, 0.0674954429268837
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(52 + frame)
obj = cameras['Camera']
obj.location = 0.7359580993652344, -3.7771921157836914, 7.4480390548706055
obj.scale = 0.9999998211860657, 0.9999997615814209, 1.0
obj.rotation_euler = 0.6697225570678711, -0.0, 0.14185751974582672
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(53 + frame)
obj = cameras['Camera']
obj.location = 1.1098518371582031, -3.777188301086426, 7.372364044189453
obj.scale = 0.9999998807907104, 0.9999998211860657, 1.0
obj.rotation_euler = 0.6818789839744568, -7.450581485102248e-09, 0.21410202980041504
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(54 + frame)
obj = cameras['Camera']
obj.location = 1.476757526397705, -3.7771830558776855, 7.274969577789307
obj.scale = 1.000000238418579, 0.9999999403953552, 1.0000001192092896
obj.rotation_euler = 0.6980742812156677, -0.0, 0.28286421298980713
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(55 + frame)
obj = cameras['Camera']
obj.location = 1.8429088592529297, -3.7771763801574707, 7.162722110748291
obj.scale = 1.000000238418579, 0.9999999403953552, 1.0
obj.rotation_euler = 0.7177272439002991, -0.0, 0.3488546311855316
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(56 + frame)
obj = cameras['Camera']
obj.location = 2.2118539810180664, -3.7771713733673096, 7.03886604309082
obj.scale = 0.9999998211860657, 0.9999999403953552, 0.9999999403953552
obj.rotation_euler = 0.7405192852020264, -0.0, 0.4122944176197052
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(57 + frame)
obj = cameras['Camera']
obj.location = 2.585707187652588, -3.7771637439727783, 6.904966354370117
obj.scale = 0.9999996423721313, 0.9999998211860657, 0.9999997019767761
obj.rotation_euler = 0.7662185430526733, -0.0, 0.47317957878112793
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(58 + frame)
obj = cameras['Camera']
obj.location = 2.9669017791748047, -3.777155876159668, 6.761153697967529
obj.scale = 0.9999998211860657, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 0.7947088479995728, -1.4901161193847656e-08, 0.5315852165222168
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(59 + frame)
obj = cameras['Camera']
obj.location = 3.3536081314086914, -3.777146577835083, 6.602686405181885
obj.scale = 0.9999997615814209, 0.9999997615814209, 0.9999998807907104
obj.rotation_euler = 0.8260979652404785, 1.4901159417490817e-08, 0.587003767490387
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(60 + frame)
obj = cameras['Camera']
obj.location = 3.7315821647644043, -3.777137517929077, 6.417652130126953
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 0.8605554699897766, -0.0, 0.6374958157539368
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(61 + frame)
obj = cameras['Camera']
obj.location = 4.058252334594727, -3.777125358581543, 6.185764312744141
obj.scale = 0.9999998807907104, 0.9999997615814209, 0.9999998807907104
obj.rotation_euler = 0.8977544903755188, -2.9802320611338473e-08, 0.6783006191253662
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(62 + frame)
obj = cameras['Camera']
obj.location = 4.273381233215332, -3.777108669281006, 5.8903727531433105
obj.scale = 1.0000003576278687, 0.9999998807907104, 1.0000001192092896
obj.rotation_euler = 0.9365482330322266, -0.0, 0.7037917971611023
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(63 + frame)
obj = cameras['Camera']
obj.location = 4.4154887199401855, -3.7770919799804688, 5.560645580291748
obj.scale = 0.9999997019767761, 0.9999998211860657, 0.9999997615814209
obj.rotation_euler = 0.976410984992981, 2.9802318834981634e-08, 0.7200490832328796
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(64 + frame)
obj = cameras['Camera']
obj.location = 4.609499454498291, -3.777073621749878, 5.248966693878174
obj.scale = 1.000000238418579, 0.9999998807907104, 1.0
obj.rotation_euler = 1.0178450345993042, -1.4901162970204496e-08, 0.7415181994438171
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(65 + frame)
obj = cameras['Camera']
obj.location = 4.886588096618652, -3.7770590782165527, 4.957681655883789
obj.scale = 0.9999997615814209, 0.9999999403953552, 0.9999997615814209
obj.rotation_euler = 1.0613203048706055, 1.4901161193847656e-08, 0.770778477191925
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(66 + frame)
obj = cameras['Camera']
obj.location = 5.181168556213379, -3.777042865753174, 4.655797481536865
obj.scale = 0.9999998807907104, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 1.1067309379577637, -0.0, 0.8001627326011658
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(67 + frame)
obj = cameras['Camera']
obj.location = 5.445913314819336, -3.7770259380340576, 4.331162929534912
obj.scale = 0.9999998807907104, 0.9999999403953552, 1.0
obj.rotation_euler = 1.1533297300338745, -0.0, 0.8251377940177917
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(68 + frame)
obj = cameras['Camera']
obj.location = 5.662207126617432, -3.777005910873413, 3.9863805770874023
obj.scale = 0.9999996423721313, 0.9999996423721313, 0.9999997019767761
obj.rotation_euler = 1.200311303138733, 1.4901162970204496e-08, 0.8445886373519897
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(69 + frame)
obj = cameras['Camera']
obj.location = 5.828554630279541, -3.7769880294799805, 3.627781867980957
obj.scale = 0.9999998807907104, 0.9999998211860657, 0.9999997615814209
obj.rotation_euler = 1.247245192527771, -1.4901161193847656e-08, 0.8589912056922913
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(70 + frame)
obj = cameras['Camera']
obj.location = 5.952057838439941, -3.7769687175750732, 3.2604007720947266
obj.scale = 0.9999997615814209, 0.9999997615814209, 0.9999997615814209
obj.rotation_euler = 1.2941147089004517, -0.0, 0.8693827986717224
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(71 + frame)
obj = cameras['Camera']
obj.location = 6.0416412353515625, -3.7769484519958496, 2.8866682052612305
obj.scale = 0.9999998807907104, 0.9999997019767761, 0.9999998211860657
obj.rotation_euler = 1.3411535024642944, 7.450580596923828e-09, 0.8767645955085754
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(72 + frame)
obj = cameras['Camera']
obj.location = 6.101911544799805, -3.776928186416626, 2.5091943740844727
obj.scale = 1.000000238418579, 1.0, 1.0
obj.rotation_euler = 1.3883618116378784, 7.450580152834618e-09, 0.8816590905189514
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(73 + frame)
obj = cameras['Camera']
obj.location = 6.134328842163086, -3.776907205581665, 2.131845474243164
obj.scale = 0.9999999403953552, 0.9999997615814209, 0.9999997615814209
obj.rotation_euler = 1.4354636669158936, -0.0, 0.8842688798904419
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(74 + frame)
obj = cameras['Camera']
obj.location = 6.149121284484863, -3.776888132095337, 1.7508783340454102
obj.scale = 0.9999998807907104, 0.9999998211860657, 0.9999998807907104
obj.rotation_euler = 1.483177661895752, -0.0, 0.8854550719261169
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(75 + frame)
obj = cameras['Camera']
obj.location = 6.146005153656006, -3.7768659591674805, 1.3667354583740234
obj.scale = 1.0000001192092896, 1.0, 0.9999999403953552
obj.rotation_euler = 1.5314867496490479, -1.862645149230957e-09, 0.8852079510688782
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(76 + frame)
obj = cameras['Camera']
obj.location = 6.1153154373168945, -3.7768468856811523, 0.9886274337768555
obj.scale = 0.9999998807907104, 1.0, 0.9999998211860657
obj.rotation_euler = 1.5792697668075562, -0.0, 0.882747232913971
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(77 + frame)
obj = cameras['Camera']
obj.location = 6.062254905700684, -3.776824951171875, 0.6117229461669922
obj.scale = 1.0, 1.0, 0.9999998807907104
obj.rotation_euler = 1.627272605895996, -0.0, 0.8784564137458801
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(78 + frame)
obj = cameras['Camera']
obj.location = 5.986579895019531, -3.7768049240112305, 0.23782730102539062
obj.scale = 1.0000001192092896, 1.0000001192092896, 1.0000001192092896
obj.rotation_euler = 1.6753621101379395, -0.0, 0.872258186340332
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(79 + frame)
obj = cameras['Camera']
obj.location = 5.889184474945068, -3.776785135269165, -0.1290760040283203
obj.scale = 1.0000001192092896, 1.0, 1.0
obj.rotation_euler = 1.7231136560440063, -7.450580596923828e-09, 0.8641432523727417
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(80 + frame)
obj = cameras['Camera']
obj.location = 5.776935577392578, -3.776766538619995, -0.49522924423217773
obj.scale = 1.0, 1.0, 1.0000001192092896
obj.rotation_euler = 1.7712619304656982, -0.0, 0.8545949459075928
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(81 + frame)
obj = cameras['Camera']
obj.location = 5.653079509735107, -3.7767465114593506, -0.864173412322998
obj.scale = 0.9999998807907104, 1.0, 1.0
obj.rotation_euler = 1.820138931274414, -0.0, 0.8438103795051575
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(82 + frame)
obj = cameras['Camera']
obj.location = 5.519182205200195, -3.776726245880127, -1.2380290031433105
obj.scale = 0.9999998807907104, 0.9999998211860657, 0.9999999403953552
obj.rotation_euler = 1.8698537349700928, 1.4901160305669237e-08, 0.8318496942520142
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(83 + frame)
obj = cameras['Camera']
obj.location = 5.375370025634766, -3.776705741882324, -1.6192240715026855
obj.scale = 0.9999999403953552, 1.0, 0.9999998807907104
obj.rotation_euler = 1.920530080795288, -1.4901162970204496e-08, 0.8186435103416443
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(84 + frame)
obj = cameras['Camera']
obj.location = 5.216897487640381, -3.776684522628784, -2.0059280395507812
obj.scale = 0.9999999403953552, 0.9999998807907104, 0.9999997615814209
obj.rotation_euler = 1.9719080924987793, -0.0, 0.8036462068557739
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(85 + frame)
obj = cameras['Camera']
obj.location = 5.031861782073975, -3.7766642570495605, -2.3839054107666016
obj.scale = 1.0, 0.9999999403953552, 0.9999997615814209
obj.rotation_euler = 2.022651433944702, -1.4901159417490817e-08, 0.7855239510536194
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(86 + frame)
obj = cameras['Camera']
obj.location = 4.799975395202637, -3.7766475677490234, -2.71057391166687
obj.scale = 0.9999999403953552, 0.9999999403953552, 0.9999998807907104
obj.rotation_euler = 2.0689291954040527, -0.0, 0.761846661567688
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(87 + frame)
obj = cameras['Camera']
obj.location = 4.504580497741699, -3.7766363620758057, -2.9257071018218994
obj.scale = 0.9999997615814209, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 2.1053826808929443, -0.0, 0.7300549745559692
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(88 + frame)
obj = cameras['Camera']
obj.location = 4.174859046936035, -3.776628017425537, -3.067812442779541
obj.scale = 0.9999998807907104, 0.9999997615814209, 0.9999997615814209
obj.rotation_euler = 2.1354920864105225, -1.4901161193847656e-08, 0.6922987699508667
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(89 + frame)
obj = cameras['Camera']
obj.location = 3.8631763458251953, -3.7766177654266357, -3.2618234157562256
obj.scale = 1.0000001192092896, 1.0000001192092896, 0.9999999403953552
obj.rotation_euler = 2.1705262660980225, -0.0, 0.6542929410934448
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(90 + frame)
obj = cameras['Camera']
obj.location = 3.571889877319336, -3.7766032218933105, -3.538909912109375
obj.scale = 1.0, 0.9999999403953552, 0.9999997615814209
obj.rotation_euler = 2.213088274002075, 1.4901162970204496e-08, 0.616650402545929
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(91 + frame)
obj = cameras['Camera']
obj.location = 3.2700061798095703, -3.776588201522827, -3.8334920406341553
obj.scale = 1.0, 0.9999998807907104, 0.9999998211860657
obj.rotation_euler = 2.256822347640991, -0.0, 0.5753991603851318
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(92 + frame)
obj = cameras['Camera']
obj.location = 2.94537353515625, -3.7765727043151855, -4.098236083984375
obj.scale = 1.0, 1.0000001192092896, 0.9999998211860657
obj.rotation_euler = 2.297131061553955, -0.0, 0.5284373760223389
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(93 + frame)
obj = cameras['Camera']
obj.location = 2.600590705871582, -3.7765610218048096, -4.3145294189453125
obj.scale = 0.9999998807907104, 0.9999998211860657, 0.9999998211860657
obj.rotation_euler = 2.332071304321289, 1.4901162970204496e-08, 0.475579172372818
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(94 + frame)
obj = cameras['Camera']
obj.location = 2.241988182067871, -3.776552677154541, -4.480877876281738
obj.scale = 0.9999998211860657, 1.0, 1.0
obj.rotation_euler = 2.3612520694732666, -0.0, 0.41737720370292664
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(95 + frame)
obj = cameras['Camera']
obj.location = 1.8746089935302734, -3.776545286178589, -4.6043806076049805
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 2.385052442550659, -1.4901159417490817e-08, 0.3544714152812958
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(96 + frame)
obj = cameras['Camera']
obj.location = 1.5008773803710938, -3.776540756225586, -4.693964004516602
obj.scale = 1.0, 1.0, 0.9999999403953552
obj.rotation_euler = 2.404010772705078, -0.0, 0.2873319387435913
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(97 + frame)
obj = cameras['Camera']
obj.location = 1.1234025955200195, -3.7765378952026367, -4.75423526763916
obj.scale = 1.0000001192092896, 1.0000001192092896, 0.9999999403953552
obj.rotation_euler = 2.4182348251342773, -0.0, 0.21671004593372345
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(98 + frame)
obj = cameras['Camera']
obj.location = 0.7460527420043945, -3.776536464691162, -4.786655426025391
obj.scale = 0.9999998807907104, 0.9999998211860657, 0.9999997615814209
obj.rotation_euler = 2.4275763034820557, 7.450580596923828e-09, 0.14384986460208893
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(99 + frame)
obj = cameras['Camera']
obj.location = 0.3650856018066406, -3.77653431892395, -4.801444053649902
obj.scale = 0.9999998211860657, 0.9999998807907104, 0.9999999403953552
obj.rotation_euler = 2.432793140411377, -0.0, 0.06870289146900177
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(100 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(101 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(102 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(103 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(104 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(105 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(106 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(107 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(108 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(109 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(110 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(111 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(112 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(113 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(114 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(115 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(116 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(117 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(118 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(119 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(120 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(121 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(122 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(123 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(124 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(125 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(126 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(127 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(128 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(129 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(130 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(131 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(132 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(133 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(134 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(135 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(136 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(137 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(138 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(139 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(140 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(141 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(142 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(143 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(144 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(145 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(146 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(147 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(148 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(149 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(150 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(151 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(152 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(153 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(154 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(155 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(156 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(157 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(158 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(159 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(160 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(161 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(162 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(163 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(164 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(165 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(166 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(167 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(168 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(169 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(170 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(171 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(172 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(173 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(174 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(175 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(176 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(177 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(178 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(179 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(180 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(181 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(182 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(183 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(184 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(185 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(186 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(187 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(188 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(189 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(190 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(191 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(192 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(193 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(194 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(195 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(196 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(197 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(198 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(199 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(200 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(201 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(202 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(203 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(204 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(205 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(206 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(207 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(208 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(209 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(210 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(211 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(212 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(213 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(214 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(215 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(216 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(217 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(218 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(219 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(220 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(221 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(222 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(223 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(224 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(225 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(226 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(227 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(228 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(229 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(230 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(231 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(232 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(233 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(234 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(235 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(236 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(237 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(238 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(239 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(240 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(241 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(242 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(243 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(244 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(245 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(246 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(247 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(248 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(249 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# new frame
scene.frame_set(250 + frame)
obj = cameras['Camera']
obj.location = -0.01905345916748047, -3.77653431892395, -4.798321723937988
obj.scale = 0.9999999403953552, 0.9999999403953552, 1.0
obj.rotation_euler = 2.4336812496185303, -0.0, -0.007860975340008736
obj.keyframe_insert('location')
obj.keyframe_insert('scale')
obj.keyframe_insert('rotation_euler')
data = obj.data
data.lens = 35.0
data.keyframe_insert('lens')

# markers
