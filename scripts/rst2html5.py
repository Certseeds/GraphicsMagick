#! /usr/bin/env python3
# -*- coding: utf-8 -*-

#* Author: Mark Mitchell
#* Copyright 2008-2022  Mark Mitchell, All Rights Reserved
#* License: see __license__ below.

"""Renders reStructuredText files to HTML with some custom HTML parts included,
such as a common header and navigation menu at the top of all HTML pages.
The header and navigation HTML blobs are kept in a separate python file,
html_fragments.py.

Usage:
    rst2html5.py [options] <RSTDOC> [<DESTINATION>]

Options:
    -h, --help      display the usage help message
    -s --stylesheet=<FILE>
                            The path to the stylesheet.
    -e --embed-stylesheet
                            If specified, the stylesheet will be embedded in the HTML.
                            If unspecified, the HTML will link to the stylesheet.

    -u --url-prefix=<PATH>
                            The value of url-prefix is prefixed to all the URLs in the
                            path to get to the top directory from the OUTFILE
                            directory.  Used to create working relative URLs in the custom
                            header and navigation menu.  Defaults to empty.
                            Example: --url-prefix=../../

Arguments:
    <RSTDOC> is the file path of the source reStructuredText document

    <DESTINATION> is the file path where the HTML output will be written.

Reads from <RSTDOC> and writes to <DESTINATION> (default is stdout)

If no <DESTINATION> is specified, output will be written to stdout.

Note:

Images referenced from the stylesheet (such as background images)
may require different image-dir paths depending on whether the stylesheet is
embedded or linked.  If linked, image URLs in the stylesheet are relative to the
stylesheet's location.  If embedded, image URLs in the stylesheet are relative
to the HTML file's path.
"""

__copyright__ = "2008 - 2022, Mark Mitchell"

__license__ = """
Copyright 2008 - 2022, Mark Mitchell

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

The Software is provided "as is", without warranty of any kind,
express or implied, including but not limited to the warranties of
merchantability, fitness for a particular purpose and noninfringement.
In no event shall the authors or copyright holders be liable for any
claim, damages or other liability, whether in an action of contract,
tort or otherwise, arising from, out of or in connection with Software
or the use or other dealings in the Software.
"""

import sys
import os

from docutils import core
import html_fragments

top_dir = os.path.abspath(os.path.dirname(__file__))

CSS = 'docutils-articles.css'
ENCODING = 'utf-8'

class Usage (Exception):
    pass

def loginfo(s):
    print(s, file=sys.stdout)

def logerror(s):
    print(s, file=sys.stderr)


def assemble_html(doc_parts, stylesheet_screen=None):
    """Constructs a complete HTML document by assembling various
    parts created by docutils.core.publish_parts and the
    templates in html_fragments.py
    """

    if stylesheet_screen is None:
        stylesheet_screen = CSS

    def get_metas():
        metas = doc_parts['meta'].split('\n')
        metas = [m.strip() for m in metas if 'name="keywords"' in m or 'name="description"' in m]
        metas = [m.replace('/>', '>') for m in metas]
        return '\n'.join(metas)

    html_head = html_fragments.make_html_head(stylesheet_screen, doc_parts['title'], get_metas())

    html = '\n'.join([
        html_head,
        '<body>',
        html_fragments.banner,
        html_fragments.nav,
        doc_parts['html_body'],
        html_fragments.footer,
        doc_parts['body_suffix'],
    ])

    return html


def make_html_parts(input_string, source_path=None, destination_path=None,
                    stylesheet=CSS, embed_stylesheet=False,
                    doctitle=1, initial_header_level=1):
    """
    Given an input string which is a reStructuredText document, returns a
    dictionary of HTML document parts created by docutils.core.publish_parts()

    Dictionary keys are the names of parts, and values are Unicode strings;
    encoding is up to the client.

    Parameters:

    - `input_string`: A multi-line text string; required.
    - `source_path`: Path to the source file or object.  Optional, but useful
      for diagnostic output (system messages).
    - `destination_path`: Path to the file or object which will receive the
      output; optional.  Used for determining relative paths (stylesheets,
      source links, etc.).
    - `doctitle`: Disable the promotion of a lone top-level section title to
      document title (and subsequent section title to document subtitle
      promotion); enabled by default.
    - `initial_header_level`: The initial level for header elements (e.g. 1
      for "<h1>").


    Parts Provided By the HTML Writer
    ---------------------------------
    body
        parts['body'] is equivalent to parts['fragment']. It is not equivalent to parts['html_body'].

    body_prefix
        parts['body_prefix'] contains:

        </head>
        <body>
        <div class="document" ...>

        and, if applicable:

        <div class="header">
        ...
        </div>

    body_pre_docinfo
        parts['body_pre_docinfo] contains (as applicable):

        <h1 class="title">...</h1>
        <h2 class="subtitle" id="...">...</h2>

    body_suffix
        parts['body_suffix'] contains:

        </div>

        (the end-tag for <div class="document">), the footer division if applicable:

        <div class="footer">
        ...
        </div>

        and:

        </body>
        </html>

    docinfo
        parts['docinfo'] contains the document bibliographic data, the docinfo
        field list rendered as a table.

    footer
        parts['footer'] contains the document footer content, meant to appear
        at the bottom of a web page, or repeated at the bottom of every printed
        page.

    fragment
        parts['fragment'] contains the document body (not the HTML <body>). In
        other words, it contains the entire document, less the document title,
        subtitle, docinfo, header, and footer.

    head
        parts['head'] contains <meta ... /> tags and the document <title>...</title>.

    head_prefix
        parts['head_prefix'] contains the XML declaration, the DOCTYPE
        declaration, the <html ...> start tag and the <head> start tag.

    header
        parts['header'] contains the document header content, meant to appear at
        the top of a web page, or repeated at the top of every printed page.

    html_body
        parts['html_body'] contains the HTML <body> content, less the <body> and </body> tags themselves.

    html_head
        parts['html_head'] contains the HTML <head> content, less the stylesheet
        link and the <head> and </head> tags themselves. Since publish_parts
        returns Unicode strings and does not know about the output encoding, the
        "Content-Type" meta tag's "charset" value is left unresolved, as "%s":

        <meta http-equiv="Content-Type" content="text/html; charset=%s" />

        The interpolation should be done by client code.

    html_prolog

        parts['html_prolog] contains the XML declaration and the doctype
        declaration. The XML declaration's "encoding" attribute's value is left
        unresolved, as "%s":

        <?xml version="1.0" encoding="%s" ?>

        The interpolation should be done by client code.

    html_subtitle
        parts['html_subtitle'] contains the document subtitle, including the
        enclosing <h2 class="subtitle"> & </h2> tags.

    html_title
        parts['html_title'] contains the document title, including the enclosing
        <h1 class="title"> & </h1> tags.

    meta
        parts['meta'] contains all <meta ... /> tags.

    stylesheet
        parts['stylesheet'] contains the embedded stylesheet or stylesheet link.

    subtitle
        parts['subtitle'] contains the document subtitle text and any inline
        markup. It does not include the enclosing <h2> & </h2> tags.

    title
        parts['title'] contains the document title text and any inline
        markup. It does not include the enclosing <h1> & </h1> tags.
    """

    # settings for publish_parts
    # input_encoding: The encoding of `input_string`.  If it is an encoded
    # 8-bit string, provide the correct encoding.  If it is a Unicode string,
    # use "unicode", the default.

    overrides = {'input_encoding': 'utf-8',
                 'doctitle_xform': doctitle,
                 'initial_header_level': initial_header_level,
                 'stylesheet_path' : stylesheet,
                 'embed_stylesheet' : embed_stylesheet,
                 'cloak_email_addresses' : True,
                }
    parts = core.publish_parts(source=input_string, source_path=source_path,
                           destination_path=destination_path,
                           writer_name='html5_polyglot', settings_overrides=overrides)
    return parts


def make_html(src_fo, dest_fo, embed_stylesheet=False, stylesheet=CSS, url_prefix=''):
    """Make an HTML file from a reStructuredText source file."""
    # Fix the url_prefix path in the banner HTML.
    # This Python tricky business is necessary because the custom docutils
    # writer, which inserts the HTML blobs, can't do it, because docutils
    # doesn't provide any way to pass an argument such as image_dir to the
    # writer.
    # There must be a better way, but I haven't figured it out yet.
    if url_prefix:
        html_fragments.url_prefix = url_prefix.rstrip('/') + '/'

    html_fragments.nav = html_fragments.make_nav()
    html_fragments.banner = html_fragments.make_banner()
    html_fragments.footer = html_fragments.make_footer()

    rst_string = src_fo.read()

    src_filepath = src_fo.name
    # change to document's original directory, so docutils can find any
    # things it might include via "include::"
    cwdsave = os.getcwd()
    if src_filepath != '<stdin>':
        os.chdir(os.path.dirname(os.path.abspath(src_filepath)))
    doc_parts = make_html_parts(rst_string, stylesheet=stylesheet, embed_stylesheet=embed_stylesheet)
    os.chdir(cwdsave)

    webpage = assemble_html(doc_parts, stylesheet_screen=stylesheet)
    try:
        dest_fo.write(webpage)
    except Exception as e:
        logerror("Failed to create output file: %s" % e)
        return 1

    return 0


def main(argv=None):
    import getopt

    sys.stdin.reconfigure(encoding=ENCODING) # iso-8859-1 is also possible
    sys.stdout.reconfigure(encoding=ENCODING)

    if argv is None:
        argv = sys.argv
    try:
        # parse command line options
        try:
            opts, args = getopt.getopt(argv[1:], 'hs:eu:',
                                        ['help',
                                         'stylesheet=',
                                         'embed-stylesheet',
                                         'url-prefix=',
                                        ])
        except getopt.GetoptError as msg:
             raise Usage(msg)

        # process options
        embed_stylesheet = False
        stylesheet = None
        url_prefix = ''

        for opt, val in opts:
            if opt in ("-h", "--help"):
                loginfo(__doc__)
                return 0

            elif opt in ("-s", "--stylesheet"):
                stylesheet = val

            elif opt in ("-e", "--embed-stylesheet"):
                embed_stylesheet = True

            elif opt in ("-u", "--url-prefix"):
                url_prefix = val

            else:
                logerror("Unrecognized option: %s\nfor help use --help" % opt)
                return 1

        # process arguments
        src_fo = sys.stdin
        dest_fo = sys.stdout

        if len(args) >= 1:
            src_filename = args[0]
            try:
                src_fo = open(src_filename, encoding=ENCODING)
            except Exception as e:
                logerror("Failed to open %s for reading: %s" % (src_filename, e))
                return 2

            if len(args) >= 2:
                dest_filename = args[1]
                try:
                    dest_fo = open(dest_filename, 'w', encoding=ENCODING)
                except Exception as e:
                    logerror("Failed to open %s for writing: %s" % (dest_filename, e))
                    return 3

        return make_html(src_fo, dest_fo, embed_stylesheet=embed_stylesheet,
                         stylesheet=stylesheet, url_prefix=url_prefix)



    except Usage as err:
        logerror(err.msg)
        logerror("for help use --help")
        return 11



if __name__ == "__main__":
    sys.exit(main())

# vim:ts=4:sw=4:expandtab
