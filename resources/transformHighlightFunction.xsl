<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="/HighlightFunction">
	<html>
	<head>
		<meta http-equiv='Content-Type' content='text/html; charset=iso-8859-1' />
		<link rel="stylesheet" href="xcode.css"/>
		<script src="highlight.pack.js">//</script>
		<script>hljs.initHighlightingOnLoad();</script>
	</head>
	<body>
		<h1>File : <xsl:value-of select="fileName"/></h1>
			<xsl:for-each select="Highlight">
					<pre><code><xsl:value-of select="BeforeFunction"/></code></pre>
					<pre><code class="InFunction"><xsl:value-of select="InFunction"/></code></pre>
					<pre><code><xsl:value-of select="AfterFunction"/></code></pre>
			</xsl:for-each>_
	</body>
	</html>
	</xsl:template>
</xsl:stylesheet>
