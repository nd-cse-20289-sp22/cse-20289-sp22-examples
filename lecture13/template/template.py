#!/usr/bin/env python3

import tornado.ioloop
import tornado.options
import tornado.web

# Constants

PORT = 9999

# Handlers

class TemplateHandler(tornado.web.RequestHandler):
    def get(self):
        name = self.get_argument('name', '')
        self.render('template.html', name=name)     # Render template with arguments

# Main Execution

def main():
    application = tornado.web.Application([
        (r'/', TemplateHandler),
    ])
    application.listen(PORT)

    tornado.options.parse_command_line()
    tornado.ioloop.IOLoop.current().start()

if __name__ == '__main__':
    main()

