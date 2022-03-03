#!/usr/bin/env python3

import logging
import random

import tornado.ioloop
import tornado.options
import tornado.web

# Constants

PORT = 9999
CODE = f'{random.randint(0, 9999):04}'

# Handlers

class eyefoneHandler(tornado.web.RequestHandler):
    def post(self):
        pin = self.get_argument('pin', '')
        self.render('eyefone.html', pin=pin, code=CODE)

    def get(self):
        self.render('eyefone.html', pin=None, code=CODE)

# Main Execution

def main():
    application = tornado.web.Application([
        (r'/', eyefoneHandler),
    ])
    application.listen(PORT)

    tornado.options.parse_command_line()

    logging.info(f'Passcode is {CODE}')

    tornado.ioloop.IOLoop.current().start()

if __name__ == '__main__':
    main()

