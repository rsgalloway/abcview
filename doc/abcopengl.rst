:mod:`alembicgl` -- Alembic Python Bindings Documentation
=======================================================

AbcOpenGL
---------

The :mod:`alembicgl` Python module is a set of Boost Python bindings for the AbcOpenGL lib, which allows
you to load an Alembic archive and draw to a GL context, e.g. from within an existing GL context such as
a PyQt QGLWidget ::

    >>> import alembicgl as abcgl
    >>> scene = abcgl.SceneWrapper("octopus.abc")
    >>> scene.draw()

A good example of the use of AbcOpenGL can be found in the SimpleAbcViewer code, and a good
example of the use of PyAbcOpenGL can be found in the GLWidget code in :doc:`AbcView </abcview>`. 


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

