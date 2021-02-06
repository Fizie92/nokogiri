#include <nokogiri.h>

VALUE cNokogiriXmlDocumentFragment;

/*
 * call-seq:
 *  new(document)
 *
 * Create a new DocumentFragment element on the +document+
 */
static VALUE
new (int argc, VALUE *argv, VALUE klass)
{
  xmlDocPtr xml_doc;
  xmlNodePtr node;
  VALUE document;
  VALUE rest;
  VALUE rb_node;

  rb_scan_args(argc, argv, "1*", &document, &rest);

  Data_Get_Struct(document, xmlDoc, xml_doc);

  node = xmlNewDocFragment(xml_doc->doc);

  noko_xml_document_pin_node(node);

  rb_node = Nokogiri_wrap_xml_node(klass, node);
  rb_obj_call_init(rb_node, argc, argv);

  if (rb_block_given_p()) { rb_yield(rb_node); }

  return rb_node;
}

void
noko_init_xml_document_fragment()
{
  assert(cNokogiriXmlNode);
  /*
   * DocumentFragment represents a DocumentFragment node in an xml document.
   */
  cNokogiriXmlDocumentFragment = rb_define_class_under(mNokogiriXml, "DocumentFragment", cNokogiriXmlNode);

  rb_define_singleton_method(cNokogiriXmlDocumentFragment, "new", new, -1);
}
