import torch
import model.net as net
import utils 
import numpy as np

model_path = "/root/git/cs230-code-examples/pytorch/nlp/experiments/base_model/best.pth.tar"
json_path = "/root/git/cs230-code-examples/pytorch/nlp/experiments/base_model/params.json"
export_trace_path = "/root/git/cs230-code-examples/pytorch/nlp/export/export-trace.pt"
export_script_path = "/root/git/cs230-code-examples/pytorch/nlp/export/export-script.pt"

params = utils.Params(json_path)
params.cuda = False# torch.cuda.is_available()   
params.unk_word = "UNK"
params.vocab_size = 368
params.number_of_tags = 9
params.pad_tag = "O"
params.pad_word = "<pad>"

model = net.Net(params).cuda() if params.cuda else net.Net(params)
utils.load_checkpoint(model_path, model)


# trace 导出
x = np.arange(100)
x = torch.LongTensor(x).reshape(1,100)
x = x #.cuda()

trace_model = torch.jit.trace(model,x)
trace_model.save(export_trace_path)

# script 导出
script_model = torch.jit.script(model)
script_model.save(export_script_path)