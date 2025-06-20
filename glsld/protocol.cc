#include "protocol.hpp"
#include <iostream>

int Protocol::handle(nlohmann::json& req)
{
    nlohmann::json resp;
    std::cerr << "start handle protocol req: \n" << req.dump(4) << std::endl;

    std::string method = req["method"];
    if (method == "initialize") {
        // std::cerr << "start handle initialize req" << std::endl;
        initialize_(req);
    } else if (method == "initialized") {
        return 0;
    } else if (method == "workspace/didChangeConfiguration") {
        return 0;
    } else if (method == "textDocument/didOpen") {
        didOpen_(req);
    } else if (method == "textDocument/definition") {
        goto_definition_(req);
    }

    return 0;
}

void Protocol::make_response_(nlohmann::json& req, nlohmann::json* result)
{
    nlohmann::json body;
    if (result) {
        body = {
            {"jsonrpc", "2.0"},
            {"id", req["id"]},
            {"result", *result},
        };
    } else {
        body = nlohmann::json::parse(R"(
			{
				"jsonrpc": "2.0",
				"result": null
			}
		)");
        body["id"] = req["id"];
    }

    std::string body_str = body.dump();

    std::string header;
    header.append("Content-Length: ");
    header.append(std::to_string(body_str.size()) + "\r\n");
    header.append("Content-Type: application/vscode-jsonrpc;charset=utf-8\r\n");
    header.append("\r\n");
    header.append(body_str);
    std::cerr << "resp to client: \n" << header << std::endl;
    std::cout << header;
    std::flush(std::cout);
}

void Protocol::initialize_(nlohmann::json& req)
{
    auto result = nlohmann::json::parse(R"(
	{
		"capabilities": {
			"textDocumentSync": {
				"openClose": true,
				"change": 1
			},
			"completionProvider": {
				"triggerCharacters": [],
				"resolveProvider": true,
				"completionItem": {
					"labelDetailsSupport": true
				}
			},
			"hoverProvider": false,
			"signatureHelpProvider": {
				"triggerCharacters": []
			},
			"declarationProvider": false,
			"definitionProvider": true,
			"typeDefinitionProvider": false,
			"implementationProvider": false,
			"referencesProvider": true,
			"documentHighlightProvider": false,
			"documentSymbolProvider": false,
			"codeActionProvider": false,
			"codeLensProvider": false,
			"documentLinkProvider": false,
			"colorProvider": false,
			"documentFormattingProvider": false,
			"documentRangeFormattingProvider": false,
			"documentOnTypeFormattingProvider": false,
			"renameProvider": false,
			"foldingRangeProvider": false,
			"executeCommandProvider": false,
			"selectionRangeProvider": false,
			"linkedEditingRangeProvider": false,
			"callHierarchyProvider": false,
			"semanticTokensProvider": false,
			"monikerProvider": false,
			"typeHierarchyProvider": false,
			"inlineValueProvider": false,
			"inlayHintProvider": false,
			"workspaceSymbolProvider": false
		}
	}
	)");

    // std::cerr << "build reqsp capabilities: " << std::endl << result.dump() << std::endl;
    nlohmann::json params = req["params"];
    workspace_.set_root(params["rootPath"]);

    init_ = true;
    // std::cerr << "init workspace at root: " << workspace_.get_root() << std::endl;
    make_response_(req, &result);
}

void Protocol::didOpen_(nlohmann::json& req)
{
    if (!init_) {
        fprintf(stderr, "server is uninitialized\n");
        return;
    }

    auto& params = req["params"];
    auto& textDoc = params["textDocument"];
    std::string uri = textDoc["uri"];
    int version = textDoc["version"];
    std::string source = textDoc["text"];
    Doc doc(uri, version, source);
    if (doc.parse({workspace_.get_root()})) {
        workspace_.add_doc(std::move(doc));
    } else {
        fprintf(stderr, "open file %s failed.\n", uri.c_str());
    }
}

void Protocol::goto_definition_(nlohmann::json& req)
{
    if (!init_) {
        fprintf(stderr, "server is uninitialized\n");
        return;
    }
    std::cerr << "handle goto definition" << std::endl;

    auto& params = req["params"];
    std::string uri = params["textDocument"]["uri"];
    int col = params["position"]["character"];
    int line = params["position"]["line"];

    std::cerr << "target sym at " << line << ":" << col << std::endl;
    auto def = workspace_.locate_symbol_def(uri, line + 1, col + 1);

    if (def) {
        nlohmann::json result;
        auto loc = def->getLoc();
        nlohmann::json start = {{"line", loc.line - 1}, {"character", loc.column - 1}};
        nlohmann::json end = {{"line", loc.line - 1}, {"character", loc.column - 1 + def->getName().size()}};
        result["uri"] = uri;
        result["range"] = {{"start", start}, {"end", end}};
        make_response_(req, &result);
    } else {
        make_response_(req, nullptr);
    }
}
