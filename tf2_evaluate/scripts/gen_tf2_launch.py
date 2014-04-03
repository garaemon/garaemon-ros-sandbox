#!/usr/bin/env python

NUM = 100

with open('../launch/tf2.launch', 'w') as f:
  f.write('<launch>\n')
  f.write('''
  <node pkg="tf2_ros"
        type="buffer_server"
        name="tf2_buffer_server" />
  ''')
  for i in range(NUM):
    msg = '''
    <node pkg="tf2_ros"
          type="static_transform_publisher"
          name="tf_broadcaster_%d"
          args="%d 0 0 0 0 0 0 map frame%d">
    </node>
    <node pkg="tf2_evaluate"
          type="tf2_echo"
          name="tf2_echo_%d"
          args="map frame%d">
    </node>
    ''' % (i, i, i, i, i)
    f.write(msg)
  f.write('</launch>')

