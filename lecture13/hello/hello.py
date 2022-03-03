#!/usr/bin/env python3

import tornado.ioloop
import tornado.options
import tornado.web

# Constants

PORT = 9999                                     # Set port to listen on

# Handlers

class HelloHandler(tornado.web.RequestHandler):
    def get(self):                              # Handler for HTTP GET request
        self.write('Hello, World!')             # Write text response

        self.write('<h1>Hello, World!</h1>')    # Write HTML response
        self.write('''
<center>
<img src="https://www.tornadoweb.org/en/stable/_images/tornado.png">
</center>
''')

# Main Execution

def main():
    application = tornado.web.Application([     # Create application
        (r'/', HelloHandler),                   # Register callback
    ])
    application.listen(PORT)                    # Set application to listen on port

    tornado.options.parse_command_line()        # Parse command line options
    tornado.ioloop.IOLoop.current().start()     # Start executing IO loop

if __name__ == '__main__':
    main()
