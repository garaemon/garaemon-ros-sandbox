#!/usr/bin/env python

NUM = 100

with open('../launch/tf.launch', 'w') as f:
  f.write('<launch>\n')
  for i in range(NUM):
    msg = '''
    <node pkg="tf"
          type="static_transform_publisher"
          name="tf_broadcaster_%d"
          args="0 0 0 0 0 0 /map /frame%d 10">
    </node>
    <node pkg="tf"
          type="tf_echo"
          name="tf_echo_%d"
          args="/map /frame%d">
    </node>
    ''' % (i, i, i, i)
    f.write(msg)
  f.write('</launch>')

