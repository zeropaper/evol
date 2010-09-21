<?php
function _evol_imagecache_default_presets() {
  $presets = array();
  
  $duotone = '$im = &$image->resource;
imagefilter($im, IMG_FILTER_GRAYSCALE);
imagetruecolortopalette($im, TRUE, 2);
imagecolorset($im, 0, 0x00, 0x00, 0x00);
imagecolorset($im, 1, 0xFF, 0xFF, 0xFF);
return $image;';
    
  $presets['duotone'] = array (
    'presetname' => 'duotone',
    'actions' => array (
      0 => 
      array (
        'weight' => '-10',
        'module' => 'imagecache',
        'action' => 'imagecache_scale_and_crop',
        'data' => 
        array (
          'width' => 100,
          'height' => 100,
        ),
      ),
      1 => 
      array (
        'weight' => '-9',
        'module' => 'imagecache_customactions',
        'action' => 'imagecache_customactions',
        'data' => 
        array (
          'text' => $duotone,
        ),
      ),
      2 => 
      array (
        'weight' => '-8',
        'module' => 'imagecache',
        'action' => 'imagecache_scale',
        'data' => 
        array (
          'width' => 200,
          'height' => 200,
          'upscale' => 1,
        ),
      ),
      3 => 
      array (
        'weight' => '0',
        'module' => 'imagecache_coloractions',
        'action' => 'imagecache_convert',
        'data' => 
        array (
          'format' => 'image/png',
        ),
      ),
      4 => 
      array (
        'weight' => '-7',
        'module' => 'imagecache_coloractions',
        'action' => 'imagecache_alpha',
        'data' => 
        array (
          'RGB' => 
          array (
            'HEX' => '000000',
          ),
          'flatten' => 0,
        ),
      ),
    ),
  );

  
  $sprite = '$im = &$image->resource;
imagefilter($im, IMG_FILTER_GRAYSCALE);
imagetruecolortopalette($im, TRUE, 2);
imagecolorset($im, 0, 0x00, 0x00, 0x00);
imagecolorset($im, 1, 0xFF, 0xFF, 0xFF);
return $image;';
  $presets['sprite'] = array (
    'presetname' => 'sprite',
    'actions' => array (
//      array (
//        'weight' => '-10',
//        'module' => 'imagecache',
//        'action' => 'imagecache_scale_and_crop',
//        'data' => 
//        array (
//          'width' => 100,
//          'height' => 100,
//        ),
//      ),
      array (
        'weight' => '-9',
        'module' => 'imagecache_customactions',
        'action' => 'imagecache_customactions',
        'data' => 
        array (
      '   text' => $sprite,
        ),
      ),
//      array (
//        'weight' => '-8',
//        'module' => 'imagecache',
//        'action' => 'imagecache_scale',
//        'data' => 
//        array (
//          'width' => 200,
//          'height' => 200,
//          'upscale' => 1,
//        ),
//      ),
//      array (
//        'weight' => '0',
//        'module' => 'imagecache_coloractions',
//        'action' => 'imagecache_convert',
//        'data' => 
//        array (
//          'format' => 'image/png',
//        ),
//      ),
//      array (
//        'weight' => '-7',
//        'module' => 'imagecache_coloractions',
//        'action' => 'imagecache_alpha',
//        'data' => 
//        array (
//          'RGB' => 
//          array (
//            'HEX' => '000000',
//          ),
//          'flatten' => 0,
//        ),
//      ),
    ),
  );
  
  $presets['duotonebig'] = $presets['duotone'];
  $presets['duotonebig']['presetname'] = 'duotonebig';
  $presets['duotonebig']['actions'][0]['data']['width'] = 480;
  $presets['duotonebig']['actions'][0]['data']['height'] = 480;
  $presets['duotonebig']['actions'][2]['data']['width'] = 960;
  $presets['duotonebig']['actions'][2]['data']['height'] = 960;
  
  return $presets;
}