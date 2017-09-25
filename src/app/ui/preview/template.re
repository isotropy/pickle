module Template = {
  let getTemplate script =>
    "\n  <!DOCTYPE html>\n  <html>\n    <head>\n      <title></title>\n      <link rel="
      stylesheet " href=" / assets /
    index.css " />\n    </head>\n    \n    <body>\n    </body>\n    \n    <script type=" text /
    javascript ">\n      " ^
    script ^ "\n    </script>\n  </html> \n  ";
};
