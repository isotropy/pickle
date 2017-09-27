const files = [
    {
      dir: 'test1/',
      path: 'test1/module1.js',
      entry: true,
      content: 'import TestModule2 from "test1/module2";const a = [1,2,3]; document.getElementById("result").innerHTML = "Hello!"',
      lastModified: 1
    },
    {
      dir: 'test1/',
      path: 'test1/module2.js',
      entry: false,
      content: '',
      lastModified: 2
    }
  ];

// const files = require('./fs/files');

exports.instantiate = function(load) {
  // const path = new URL(load.address).pathname;
  // if (path !== "/0") {
  //   const file = files.filter(file => file.path === path[path.length - 1]);
  //   return file[0].content;
  // }
  // return files[0].content;
  const path = load.address.match(/fs\/(.*)!/);
  const file = files.filter(file => file.path === path[path.length - 1]);
  load.metadata.sourceMap.sourcesContent[0] = file[0].content;
  return load;
}